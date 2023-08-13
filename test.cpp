//
// Created by lxg on 2023/8/10.
//

#include "lib/microtex.h"
#include "graphic_skia.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "skia-utils/skia_utils.h"

#include <iostream>
#include "fstream"
#include "dirent.h"
#include "map"

using namespace std;
using namespace microtex;

void listFiles(const std::string &path, std::map<std::string, std::string> &map) {
    DIR *dir = opendir(path.data());
    if (!dir) {
        return;
    }
    struct dirent *ptr;
    while (ptr = readdir(dir)) {
        if (ptr->d_type == 8) {
            std::string name(ptr->d_name);
            int pos = name.rfind(".latex");
            if (pos != std::string::npos) {
                map.emplace(path + name, path + "cppOut/" + name.substr(0, pos) + ".png");
            }
        }
    }
    closedir(dir);
}

bool isBracesMatched(const std::string& content, size_t start, const std::string& closeBrackets) {
    size_t index1 = content.find('}', start);
    size_t index2 = content.find('{', start);
    size_t index3 = content.find(closeBrackets, start);
    return index3 <= index1 || index2 <= index1;
}

std::string ensureBracketsMatched(const std::string& latex) {
    std::string result = latex;
    size_t index = 0;
    std::string closeParentheses = "\\right)";
    std::string closeBrackets = "\\right]";
    std::string closeBraces = "\\}";
    while ((index = result.find("\\left", index)) != std::string::npos) {
        char ch = result[index + 5];
        if ((ch == '(' || ch == '[')
            && !isBracesMatched(result, index + 6, ch == '(' ? closeParentheses : closeBrackets)) {
            result.insert(index, "}");
            result.insert(index + 7, "{");
            index += 8;
        } else if (ch == '\\' && result[index + 6] == '{'
                   && !isBracesMatched(result, index + 7, closeBraces)) {
            result.insert(index, "}");
            result.insert(index + 8, "{");
            index += 9;
        } else {
            index += 5;
        }
    }
    return result;
}

void test1(std::map<std::string, std::string> &map) {

    float _textSize = 20.f;
    color _foreground = BLACK;
    color _background = WHITE;
    float _padding = 10.f;
    float _maxWidth = 720.f;
//    std::string code = "${\\pi }^{4}+{\\pi }^{5}\\approx {e}^{6}$";
    for (const auto &item: map) {
        std::string code;
        std::ifstream stream(item.first);
        std::getline(stream, code, '\0');
        auto r = MicroTeX::parse(code, _maxWidth, _textSize, _textSize / 3.f, _foreground);
        const float w = r->getWidth() + _padding * 2;
        const float h = r->getHeight() + _padding * 2;

        SkBitmap bitmap;
        bitmap.allocN32Pixels(w, h);
        SkCanvas canvas(bitmap);

        Graphics2D_skia g2(&canvas);
        if (!isTransparent(_background)) {
            g2.setColor(_background);
            g2.fillRect(0, 0, w, h);
        }

        r->draw(g2, _padding, _padding);
        delete r;
        SkUtils::compress(item.second, bitmap);
    }

}

int main(int argc, char* argv[]) {
    const FontSrcFile math{"res/firamath/FiraMath-Regular.clm1", "res/firamath/FiraMath-Regular.otf"};
    MicroTeX::init(math);
    PlatformFactory::registerFactory("skia", std::make_unique<PlatformFactory_skia>());
    PlatformFactory::activate("skia");
    std::map<std::string, std::string> map;
    listFiles("/home/luo/WorkSpace/resources/latex/", map);
    test1(map);
    MicroTeX::release();
}