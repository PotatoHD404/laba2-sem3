//
// Created by kmv026 on 10.10.2021.
//

#pragma once

class NotImplemented : public std::logic_error {
private:

    std::string _text;

public:

    NotImplemented() :
            NotImplemented("Not Implemented", __FUNCTION__) {
    }

    explicit NotImplemented(const char *message) :
            NotImplemented(message, __FUNCTION__) {
    }

    [[nodiscard]] const char *what() const noexcept final {
        return _text.c_str();
    }

    NotImplemented(const char *message, const char *function) :
            std::logic_error("Not Implemented") {
        _text = message;
        _text += " : ";
        _text += function;
    }
};

