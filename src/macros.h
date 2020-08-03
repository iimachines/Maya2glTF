#pragma once

// A macro to disallow the copy/move constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_MOVE_ASSIGN(TypeName)                                    \
    TypeName(const TypeName &) = delete;                                       \
    void operator=(const TypeName &) = delete;                                 \
    TypeName(TypeName &&) = delete;                                            \
    void operator=(TypeName &&) = delete;

#define DEFAULT_COPY_MOVE_ASSIGN(TypeName)                                     \
    TypeName(const TypeName &other) = default;                                 \
    TypeName(TypeName &&other) = default;                                      \
    TypeName &operator=(const TypeName &other) = default;                      \
    TypeName &operator=(TypeName &&other) = default;

#define DEFAULT_COPY_MOVE_ASSIGN_DTOR(TypeName)                                \
    ~TypeName() = default;                                                     \
    DEFAULT_COPY_MOVE_ASSIGN(TypeName)

#define DEFAULT_COPY_MOVE_ASSIGN_CTOR_DTOR(TypeName)                           \
    TypeName() = default;                                                      \
    DEFAULT_COPY_MOVE_ASSIGN_DTOR(TypeName)
