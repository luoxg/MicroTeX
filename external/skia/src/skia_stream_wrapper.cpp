//
// Created by lxg on 2023/8/3.
//
#include "skia-utils/skia_stream_wrapper.h"
#include "src/base/SkSafeMath.h"

std::unique_ptr<SkStreamWrapper> SkStreamWrapper::Make(const std::shared_ptr<std::istream> &in) {
    return in == nullptr ? nullptr : std::make_unique<SkStreamWrapper>(in);
}

SkStreamWrapper::SkStreamWrapper(const std::shared_ptr<std::istream> &in) : fStream(in) {
    fStart = fStream->tellg();
    fStream->seekg(0, std::ios::end);
    fEnd = fStream->tellg();
    fStream->seekg(fStart);
}

SkStreamWrapper::SkStreamWrapper(const std::shared_ptr<std::istream> &in, size_t start, size_t end) : fStream(in), fStart(start), fEnd(end) {

}

size_t SkStreamWrapper::getPosition() const {
    return fStream->tellg();
}

bool SkStreamWrapper::seek(size_t position) {
    fStream->seekg(position);
    return true;
}

bool SkStreamWrapper::move(long offset) {
    if (offset < 0) {
        if (offset == std::numeric_limits<long>::min() ||
            !SkTFitsIn<size_t>(-offset) ||
            (size_t) (-offset) >= this->getPosition()) {
            fStream->seekg(fStart);
        } else {
            fStream->seekg(fStart + offset);
        }
    } else if (!SkTFitsIn<size_t>(offset)) {
        fStream->seekg(fEnd);
    } else {
        size_t current = std::min(SkSafeMath::Add(fStream->tellg(), (size_t) offset), fEnd);
        fStream->seekg(current);
    }
    return true;
}

size_t SkStreamWrapper::read(void *buffer, size_t size) {
    fStream->read((char*)buffer, size);
    return fStream->gcount();
}

bool SkStreamWrapper::isAtEnd() const {
    return fStream->eof();
}

bool SkStreamWrapper::rewind() {
    fStream->seekg(fStart);
    return true;
}

SkStreamWrapper *SkStreamWrapper::onDuplicate() const {
    fStream->seekg(fStart);
    return new SkStreamWrapper(fStream, fStart, fEnd);
}

SkStreamWrapper *SkStreamWrapper::onFork() const {
    return new SkStreamWrapper(fStream, fStart, fEnd);
}

