//
// Created by lxg on 2023/7/17.
//

#ifndef SkSVGStyle_DEFINED
#define SkSVGStyle_DEFINED

#include "modules/svg/include/SkSVGNode.h"
#include "modules/svg/include/SkSVGTypes.h"
#include "modules/svg/include/SkSVGText.h"
#include "src/xml/SkDOM.h"
#include <vector>
#include <map>
#include <set>

class StyleSheet;
struct Declaration;

class SK_API SkSVGStyle final : public SkSVGNode {
public:
    static sk_sp<SkSVGStyle> Make() { return sk_sp<SkSVGStyle>(new SkSVGStyle()); }

    void appendChild(sk_sp<SkSVGNode>) override;

    void setStyleSheet(StyleSheet* styleSheet);

    SVG_ATTR(Type   , SkString, SkString())

protected:
    bool onPrepareToRender(SkSVGRenderContext*) const override;
    void onRender(const SkSVGRenderContext&) const override;
    SkPath onAsPath(const SkSVGRenderContext&) const override;

private:
    SkSVGStyle();

    bool parseAndSetAttribute(const char*, const char*) override;

    SkString fContent;
    sk_sp<StyleSheet> fSheet;

    using INHERITED = SkSVGNode;
};

struct Declaration {
    int specificity;
    std::string name;
    std::string value;
};

struct SimpleSelector;
using DeclarationList = std::vector<Declaration>;

using Selector = std::vector<SimpleSelector>;
using SelectorList = std::vector<Selector>;

struct Rule {
    SelectorList selectors;
    DeclarationList declarations;
};

struct AttributeSelector {
    enum class MatchType {
        None,
        Equal,
        Includes,
        DashMatch,
        StartsWith,
        EndsWith,
        Contains
    };

    MatchType matchType{MatchType::None};
    std::string name;
    std::string value;
};

struct PseudoClassSelector {
    enum class Type {
        Unknown,
        Empty,
        Root,
        Is,
        Not,
        FirstChild,
        LastChild,
        OnlyChild,
        FirstOfType,
        LastOfType,
        OnlyOfType
    };

    Type type{Type::Unknown};
    SelectorList subSelectors;
};

const static std::string Star = "star";

struct SimpleSelector {
    enum class Combinator {
        Descendant,
        Child,
        DirectAdjacent,
        InDirectAdjacent
    };

    Combinator combinator{Combinator::Descendant};
    std::string name{Star};
    std::vector<AttributeSelector> attributeSelectors;
    std::vector<PseudoClassSelector> pseudoClassSelectors;
};

class RuleData {
public:
    RuleData() = default;
    RuleData(const Selector& selector, const DeclarationList& declarations, uint32_t specificity, uint32_t position);

    const Selector& selector() const { return fSelector; }
    const DeclarationList& declarations() const { return fDeclarations; }
    const uint32_t& specificity() const { return fSpecificity; }
    const uint32_t& position() const { return fPosition; }

    bool match(const SkDOM* dom, const SkDOM::Node* xmlNode) const;

private:
    static bool matchSimpleSelector(const SimpleSelector& selector, const SkDOM* dom, const SkDOM::Node* xmlNode);
    static bool matchAttributeSelector(const AttributeSelector& selector, const SkDOM* dom, const SkDOM::Node* xmlNode);
    static bool matchPseudoClassSelector(const PseudoClassSelector& selector, const SkDOM* dom, const SkDOM::Node* xmlNode);

private:
    Selector fSelector;
    DeclarationList fDeclarations;
    uint32_t fSpecificity;
    uint32_t fPosition;
};

inline bool operator<(const RuleData& a, const RuleData& b) { return std::tie(a.specificity(), a.position()) < std::tie(b.specificity(), b.position()); }
inline bool operator>(const RuleData& a, const RuleData& b) { return std::tie(a.specificity(), a.position()) > std::tie(b.specificity(), b.position()); }

class StyleSheet : public SkRefCnt {
public:
    StyleSheet() = default;

    bool parse(const std::string& content);
    void add(const Rule& rule);
    bool empty() const { return fRules.empty(); }

    const std::multiset<RuleData>& rules() const { return fRules; }

private:
    static bool parseAtRule(const char*& ptr, const char* end);
    static bool parseRule(const char*& ptr, const char* end, Rule& rule);
    static bool parseSelectors(const char*& ptr, const char* end, SelectorList& selectors);
    static bool parseDeclarations(const char*& ptr, const char* end, DeclarationList& declarations);
    static bool parseSelector(const char*& ptr, const char* end, Selector& selector);
    static bool parseSimpleSelector(const char*& ptr, const char* end, SimpleSelector& simpleSelector);

private:
    std::multiset<RuleData> fRules;
    uint32_t fPosition{0};
};

#endif //SkSVGStyle_DEFINED
