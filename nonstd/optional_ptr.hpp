
#pragma once

#include <memory>

namespace nonstd {

template <typename T>
class optional_ptr : public std::unique_ptr<T> {

public:
    inline optional_ptr() { }
    inline optional_ptr(T *ptr) : std::unique_ptr<T>(ptr) { }
    inline optional_ptr(const optional_ptr<T> &orig) : std::unique_ptr<T>(orig.get() ? new T(*orig) : nullptr) { }
    inline optional_ptr(optional_ptr<T> &&orig) : std::unique_ptr<T>((std::unique_ptr<T> &&) orig) { }
    inline optional_ptr<T> & operator=(const optional_ptr<T> &orig) {
        if (this != &orig)
            *static_cast<std::unique_ptr<T> *>(this) = std::unique_ptr<T>(orig.get() ? new T(*orig) : nullptr);
        return *this;
    }
    inline optional_ptr<T> & operator=(optional_ptr<T> &&orig) {
        std::unique_ptr<T>::operator=((std::unique_ptr<T> &&) orig);
        return *this;
    }
    inline optional_ptr<T> & operator=(T *ptr) {
        std::unique_ptr<T>::reset(ptr);
        return *this;
    }
    inline bool has_value() const {
        return std::unique_ptr<T>::get() != nullptr;
    }

};

}
