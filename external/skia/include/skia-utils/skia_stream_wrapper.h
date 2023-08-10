//
// Created by lxg on 2023/8/3.
//

#ifndef CBOX_SKIA_STREAM_WRAPPER_H
#define CBOX_SKIA_STREAM_WRAPPER_H

#include "fstream"
#include "include/core/SkStream.h"

class SK_API SkStreamWrapper : public SkStreamSeekable {
public:
    static std::unique_ptr<SkStreamWrapper> Make(const std::shared_ptr<std::istream> &in);

    SkStreamWrapper(const std::shared_ptr<std::istream> &in);

    std::unique_ptr<SkStreamWrapper> duplicate() const {
        return std::unique_ptr<SkStreamWrapper>(this->onDuplicate());
    }

    std::unique_ptr<SkStreamWrapper> fork() const {
        return std::unique_ptr<SkStreamWrapper>(this->onFork());
    }

    bool hasPosition() const override { return true; }

    size_t getPosition() const override;

    bool seek(size_t position) override;

    bool move(long offset) override;

    size_t read(void *buffer, size_t size) override;

    bool isAtEnd() const override;

    bool rewind() override;

private:
    SkStreamWrapper(const std::shared_ptr<std::istream> &in, size_t start, size_t end);

    SkStreamWrapper *onDuplicate() const override;

    SkStreamWrapper *onFork() const override;

    std::shared_ptr<std::istream> fStream;
    size_t fStart{0};
    size_t fEnd{0};
};

#endif //CBOX_SKIA_STREAM_WRAPPER_H
