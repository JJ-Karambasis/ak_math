#ifndef AK_MATH_H
#define AK_MATH_H

#ifdef AK_MATH_STATIC
#define AK_MATH_DEF static
#else
#ifdef __cpluscplus
#define AK_MATH_DEF extern "C"
#else
#define AK_MATH_DEF extern
#endif // __cplusplus
#endif //AK_OS_STATIC

#define AKM_PI 3.14159265359f
#define AKM_To_Radians(v) ((v)*AKM_PI/180.0f)
#define AKM_To_Degrees(v) ((v)*180.0f/AKM_PI)

union ak_v2f
{
    float Data[2];
    struct { float x; float y; };
};

union ak_v3f
{
    float Data[3];
    struct { float x; float y; float z; };
    struct { ak_v2f xy; float __unused0__; };
};

union ak_v4f
{
    float Data[4];
    struct { float x; float y; float z; float w; };
    struct { ak_v3f xyz; float __unused0__; };
};

union ak_quatf
{
    float Data[4];
    struct { float x; float y; float z; float w; };
    struct { ak_v4f q; };
    struct { ak_v3f v; float s; };
};

union ak_m3f
{
    float  Data[9];
    ak_v3f Rows[3];
    struct { ak_v3f x; ak_v3f y; ak_v3f z; };
    struct
    {
        float m00; float m01; float m02;
        float m10; float m11; float m12;
        float m20; float m21; float m22;
    };
};

union ak_m4f
{
    float Data[16];
    ak_v4f Rows[4];
    struct 
    { 
        ak_v3f x; float __unused0__; 
        ak_v3f y; float __unused1__;
        ak_v3f z; float __unused2__;
        ak_v3f t; float __unused3__;
    };
    
    struct
    {
        float m00; float m01; float m02; float m03;
        float m10; float m11; float m12; float m13;
        float m20; float m21; float m22; float m23;
        float m30; float m31; float m32; float m33;
    };
};

ak_v2f AKM_V2(float x, float y);

bool operator==(const ak_v2f& A, const ak_v2f& B);
bool operator!=(const ak_v2f& A, const ak_v2f& B);

ak_v3f AKM_V3(float x, float y, float z);

ak_v3f operator+(const ak_v3f& A, const ak_v3f& B);
ak_v3f& operator+=(ak_v3f& A, const ak_v3f& B);


ak_v3f operator*(const ak_v3f& A, float B);
ak_v3f operator*(float A, const ak_v3f& B);

float AKM_Dot(const ak_v3f& A, const ak_v3f& B);
float AKM_Sq_Mag(const ak_v3f& V);
float AKM_Mag(const ak_v3f& V);
ak_v3f AKM_Norm(const ak_v3f& V);
ak_v3f AKM_Cross(const ak_v3f& A, const ak_v3f& B);
ak_v3f AKM_Rotate(const ak_v3f& Direction, const ak_quatf& Orientation);

ak_v4f AKM_V4(float x, float y, float z, float w);
ak_v4f AKM_V4(const ak_v3f& V, float w);
float AKM_Dot(const ak_v4f& A, const ak_v4f& B);
ak_v4f operator*(const ak_v4f& A, const ak_m4f& B);

ak_m3f AKM_ToMatrix(const ak_quatf& Orientation);

ak_m4f AKM_M4(float V);
ak_m4f AKM_IdentityM4();
ak_m4f AKM_TransposeM4(const ak_m4f& M);
ak_m4f AKM_TranslateM4(const ak_v3f& V);
ak_m4f AKM_TransformM4(const ak_v3f& P, const ak_m3f& Orientation, const ak_v3f& S);
ak_m4f AKM_TransformM4(const ak_v3f& P, const ak_quatf& Orientation);
ak_m4f AKM_Inverse_TransformM4(const ak_v3f& P, const ak_m3f& Orientation, const ak_v3f& S);
ak_m4f AKM_Inverse_TransformM4(const ak_v3f& P, const ak_quatf& Orientation);
ak_m4f operator*(const ak_m4f& A, const ak_m4f& B);

ak_quatf AKM_Quat(const ak_v3f& V, float S);
ak_quatf AKM_Quat_RotX(float Pitch);
ak_quatf AKM_Quat_RotZ(float Roll);
ak_quatf AKM_Quat_RotY(float Yaw);
float AKM_Dot(const ak_quatf& A, const ak_quatf& B);
float AKM_Sq_Mag(const ak_quatf& Q);
float AKM_Mag(const ak_quatf& Q);
ak_quatf AKM_Norm(const ak_quatf& Q);
ak_quatf operator*(const ak_quatf& A, float B);
ak_quatf operator*(const ak_quatf& A, const ak_quatf& B);

#endif //AK_MATH_H

#ifdef AK_MATH_IMPLEMENTATION

#if !defined(AKM_SQRT) || !defined(AKM_SIN) || !defined(AKM_COS) || !defined(AKM_TAN)
#include <math.h>
#endif

#ifndef AKM_SQRT
#define AKM_SQRT(v) sqrtf(v)
#endif //AKM_SQRT

#ifndef AKM_SIN
#define AKM_SIN(v) sinf(v)
#endif //AKM_SIN

#ifndef AKM_COS
#define AKM_COS(v) cosf(v)
#endif //AKM_SIN

#ifndef AKM_TAN
#define AKM_TAN(v) tanf(v)
#endif //AKM_SIN

#define AKM__EPSILON32 1.1920929e-7f

inline float AKM__Abs(float A)
{
    return A < 0 ? -A : A;
}

inline bool AKM__Equal_Approx(float A, float Eps)
{
    return AKM__Abs(A) < Eps;
}

inline bool AKM__Equal_Zero_Eps(float A)
{
    return AKM__Equal_Approx(A, AKM__EPSILON32);
}

ak_v2f AKM_V2(float x, float y)
{
    ak_v2f Result = {x, y};
    return Result;
}

bool operator==(const ak_v2f& A, const ak_v2f& B)
{
    return A.x == B.x && A.y == B.y;
}

bool operator!=(const ak_v2f& A, const ak_v2f& B)
{
    return A.x != B.x || A.y != B.y;
}

ak_v3f AKM_V3(float x, float y, float z)
{
    ak_v3f Result = {x, y, z};
    return Result;
}

ak_v3f operator+(const ak_v3f& A, const ak_v3f& B)
{
    ak_v3f Result = {A.x+B.x, A.y+B.y, A.z+B.z};
    return Result;
}

ak_v3f& operator+=(ak_v3f& A, const ak_v3f& B)
{
    A = A+B;
    return A;
}

ak_v3f operator*(const ak_v3f& A, float B)
{
    ak_v3f Result = {A.x*B, A.y*B, A.z*B};
    return Result;
}

ak_v3f operator*(float A, const ak_v3f& B)
{
    ak_v3f Result = {A*B.x, A*B.y, A*B.z};
    return Result;
}

float AKM_Dot(const ak_v3f& A, const ak_v3f& B)
{
    float Result = A.x*B.x + A.y*B.y + A.z*B.z;
    return Result;
}

float AKM_Sq_Mag(const ak_v3f& V)
{
    return AKM_Dot(V, V);
}

float AKM_Mag(const ak_v3f& V)
{
    return AKM_SQRT(AKM_Sq_Mag(V));
}

ak_v3f AKM_Norm(const ak_v3f& V)
{
    float Length = AKM_Mag(V);
    if(AKM__Equal_Zero_Eps(Length)) return {};
    Length = 1.0f/Length;
    return V*Length;
}

ak_v3f AKM_Cross(const ak_v3f& A, const ak_v3f& B)
{
    ak_v3f Result = {A.y*B.z - A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x};
    return Result;
}

ak_v3f AKM_Rotate(const ak_v3f& Direction, const ak_quatf& Orientation)
{
    ak_v3f Result = ((2 * AKM_Dot(Orientation.v, Direction) * Orientation.v) + 
                     ((Orientation.s*Orientation.s - AKM_Sq_Mag(Orientation.v))*Direction) +
                     (2*Orientation.s*AKM_Cross(Orientation.v, Direction)));
    return Result;
}

ak_v4f AKM_V4(float x, float y, float z, float w)
{
    ak_v4f Result = {x, y, z, w};
    return Result;
}

ak_v4f AKM_V4(const ak_v3f& V, float w)
{
    return AKM_V4(V.x, V.y, V.z, w);
}

float AKM_Dot(const ak_v4f& A, const ak_v4f& B)
{
    float Result = A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
    return Result;
}

ak_v4f operator*(const ak_v4f& V, const ak_m4f& B)
{
    ak_m4f BTransposed = AKM_TransposeM4(B);
    
    ak_v4f Result;
    Result.x = AKM_Dot(V, BTransposed.Rows[0]);
    Result.y = AKM_Dot(V, BTransposed.Rows[1]);
    Result.z = AKM_Dot(V, BTransposed.Rows[2]);
    Result.w = AKM_Dot(V, BTransposed.Rows[3]);
    return Result;
}

ak_m3f AKM_ToMatrix(const ak_quatf& Q)
{
    float qxqy = Q.x*Q.y;
    float qwqz = Q.w*Q.z;
    float qxqz = Q.x*Q.z;
    float qwqy = Q.w*Q.y;
    float qyqz = Q.y*Q.z;
    float qwqx = Q.w*Q.x;
    
    float qxqx = Q.x*Q.x;
    float qyqy = Q.y*Q.y;
    float qzqz = Q.z*Q.z;
    
    ak_m3f Result = 
    {
        1 - 2*(qyqy+qzqz), 2*(qxqy+qwqz),     2*(qxqz-qwqy),   
        2*(qxqy-qwqz),     1 - 2*(qxqx+qzqz), 2*(qyqz+qwqx),   
        2*(qxqz+qwqy),     2*(qyqz-qwqx),     1 - 2*(qxqx+qyqy)
    };
    
    return Result;
}

ak_m4f AKM_M4(float V)
{
    ak_m4f Result = 
    {
        V, 0, 0, 0, 
        0, V, 0, 0, 
        0, 0, V, 0, 
        0, 0, 0, V
    };
    
    return Result;
}

ak_m4f AKM_IdentityM4()
{
    return AKM_M4(1.0f);
}

ak_m4f AKM_TransposeM4(const ak_m4f& M)
{
    ak_m4f Result;
    Result.m00 = M.m00;
    Result.m10 = M.m01;
    Result.m20 = M.m02;
    Result.m30 = M.m03; 
    
    Result.m01 = M.m10;
    Result.m11 = M.m11;
    Result.m21 = M.m12;
    Result.m31 = M.m13; 
    
    Result.m02 = M.m20;
    Result.m12 = M.m21;
    Result.m22 = M.m22;
    Result.m32 = M.m23;
    
    Result.m03 = M.m30;
    Result.m13 = M.m31;
    Result.m23 = M.m32;
    Result.m33 = M.m33; 
    
    return Result;
}

ak_m4f AKM_TranslateM4(const ak_v3f& V)
{
    ak_m4f Result = AKM_IdentityM4();
    Result.t = V;
    return Result;
}

ak_m4f AKM_TransformM4(const ak_v3f& P, const ak_m3f& Orientation, const ak_v3f& S)
{
    ak_m4f Result = {};
    Result.x = Orientation.x*S.x;
    Result.y = Orientation.y*S.y;
    Result.z = Orientation.z*S.z;
    Result.t = P;
    Result.Data[15] = 1.0f;
    return Result;
}

ak_m4f AKM_TransformM4(const ak_v3f& P, const ak_quatf& Orientation)
{
    return AKM_TransformM4(P, AKM_ToMatrix(Orientation), AKM_V3(1.0f, 1.0f, 1.0f));
}

ak_m4f AKM_Inverse_TransformM4(const ak_v3f& P, const ak_m3f& Orientation, const ak_v3f& S)
{
    ak_v3f X = Orientation.x*S.x;
    ak_v3f Y = Orientation.y*S.y;
    ak_v3f Z = Orientation.z*S.z;
    ak_v3f T = {-AKM_Dot(P, X), -AKM_Dot(P, Y), -AKM_Dot(P, Z)};
    
    ak_m4f Result = 
    {
        X.x, Y.x, Z.x, 0, 
        X.y, Y.y, Z.y, 0,
        X.z, Y.z, Z.z, 0, 
        T.x, T.y, T.z, 1
    };
    
    return Result;
}

ak_m4f AKM_Inverse_TransformM4(const ak_v3f& P, const ak_quatf& Orientation)
{
    return AKM_Inverse_TransformM4(P, AKM_ToMatrix(Orientation), AKM_V3(1.0f, 1.0f, 1.0f));
}

ak_m4f operator*(const ak_m4f& A, const ak_m4f& B)
{
    ak_m4f Result;
    
    ak_m4f BTransposed = AKM_TransposeM4(B);
    
    Result.Data[0]  = AKM_Dot(A.Rows[0], BTransposed.Rows[0]);
    Result.Data[1]  = AKM_Dot(A.Rows[0], BTransposed.Rows[1]);
    Result.Data[2]  = AKM_Dot(A.Rows[0], BTransposed.Rows[2]);
    Result.Data[3]  = AKM_Dot(A.Rows[0], BTransposed.Rows[3]);
    
    Result.Data[4]  = AKM_Dot(A.Rows[1], BTransposed.Rows[0]);
    Result.Data[5]  = AKM_Dot(A.Rows[1], BTransposed.Rows[1]);
    Result.Data[6]  = AKM_Dot(A.Rows[1], BTransposed.Rows[2]);
    Result.Data[7]  = AKM_Dot(A.Rows[1], BTransposed.Rows[3]);
    
    Result.Data[8]  = AKM_Dot(A.Rows[2], BTransposed.Rows[0]);
    Result.Data[9]  = AKM_Dot(A.Rows[2], BTransposed.Rows[1]);
    Result.Data[10] = AKM_Dot(A.Rows[2], BTransposed.Rows[2]);
    Result.Data[11] = AKM_Dot(A.Rows[2], BTransposed.Rows[3]);
    
    Result.Data[12] = AKM_Dot(A.Rows[3], BTransposed.Rows[0]);
    Result.Data[13] = AKM_Dot(A.Rows[3], BTransposed.Rows[1]);
    Result.Data[14] = AKM_Dot(A.Rows[3], BTransposed.Rows[2]);
    Result.Data[15] = AKM_Dot(A.Rows[3], BTransposed.Rows[3]);
    
    return Result;
}

ak_quatf AKM_Quat(const ak_v3f& V, float S)
{
    ak_quatf Result = {V.x, V.y, V.z, S};
    return Result;
}

ak_quatf AKM_Quat_RotX(float Pitch)
{
    ak_quatf Result = {};
    Result.x = AKM_SIN(Pitch/2);
    Result.w = AKM_COS(Pitch/2);
    return Result;
}

ak_quatf AKM_Quat_RotY(float Yaw)
{
    ak_quatf Result = {};
    Result.y = AKM_SIN(Yaw/2);
    Result.w = AKM_COS(Yaw/2);
    return Result;
}

ak_quatf AKM_Quat_RotZ(float Roll)
{
    ak_quatf Result = {};
    Result.z = AKM_SIN(Roll/2);
    Result.w = AKM_COS(Roll/2);
    return Result;
}

float AKM_Dot(const ak_quatf& A, const ak_quatf& B)
{
    return {A.x*B.x+A.y*B.y+A.z*B.z+A.w*B.w};
}

float AKM_Sq_Mag(const ak_quatf& Q)
{
    return AKM_Dot(Q, Q);
}

float AKM_Mag(const ak_quatf& Q)
{
    return AKM_SQRT(AKM_Sq_Mag(Q));
}

ak_quatf AKM_Norm(const ak_quatf& Q)
{
    float Length = AKM_Mag(Q);
    if(AKM__Equal_Zero_Eps(Length)) return {0, 0, 0, 1};
    Length = 1.0f/Length;
    return Q*Length;
}

ak_quatf operator*(const ak_quatf& A, float B)
{
    ak_quatf Result = {A.x*B, A.y*B, A.z*B, A.w*B};
    return Result;
}

ak_quatf operator*(const ak_quatf& A, const ak_quatf& B)
{
    ak_quatf Result = AKM_Quat(AKM_Cross(A.v, B.v) + B.s*A.v + B.v*A.s, 
                               A.s*B.s - AKM_Dot(A.v, B.v));
    return Result;  
}

#endif //AK_MATH_IMPLEMENTATION


#ifdef AK_MATH_TESTS

/*
   The latest version of this library is available on GitHub;
   https://github.com/sheredom/utest.h
*/

/*
   This is free and unencumbered software released into the public domain.

   Anyone is free to copy, modify, publish, use, compile, sell, or
   distribute this software, either in source code form or as a compiled
   binary, for any purpose, commercial or non-commercial, and by any
   means.

   In jurisdictions that recognize copyright laws, the author or authors
   of this software dedicate any and all copyright interest in the
   software to the public domain. We make this dedication for the benefit
   of the public at large and to the detriment of our heirs and
   successors. We intend this dedication to be an overt act of
   relinquishment in perpetuity of all present and future rights to this
   software under copyright law.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.

   For more information, please refer to <http://unlicense.org/>
*/

#ifndef SHEREDOM_UTEST_H_INCLUDED
#define SHEREDOM_UTEST_H_INCLUDED

#ifdef _MSC_VER
/*
   Disable warning about not inlining 'inline' functions.
*/
#pragma warning(disable : 4710)

/*
   Disable warning about inlining functions that are not marked 'inline'.
*/
#pragma warning(disable : 4711)

#if _MSC_VER > 1900
/*
  Disable warning about preprocessor macros not being defined in MSVC headers.
*/
#pragma warning(disable : 4668)

/*
  Disable warning about no function prototype given in MSVC headers.
*/
#pragma warning(disable : 4255)

/*
  Disable warning about pointer or reference to potentially throwing function.
*/
#pragma warning(disable : 5039)
#endif

#pragma warning(push, 1)
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1920)
typedef __int64 utest_int64_t;
typedef unsigned __int64 utest_uint64_t;
typedef unsigned __int32 utest_uint32_t;
#else
#include <stdint.h>
typedef int64_t utest_int64_t;
typedef uint64_t utest_uint64_t;
typedef uint32_t utest_uint32_t;
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#if defined(__cplusplus)
#define UTEST_C_FUNC extern "C"
#else
#define UTEST_C_FUNC
#endif

#if defined(_MSC_VER) \
|| defined(__MINGW64__) \
|| defined(__MINGW32__)

#if defined(__MINGW64__) || defined(__MINGW32__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif

// define UTEST_USE_OLD_QPC before #include "utest.h" to use old QueryPerformanceCounter
#ifndef UTEST_USE_OLD_QPC
#pragma warning(push, 0)
#include <Windows.h>
#pragma warning(pop)

typedef LARGE_INTEGER utest_large_integer;
#else
//use old QueryPerformanceCounter definitions (not sure is this needed in some edge cases or not)
//on Win7 with VS2015 these extern declaration cause "second C linkage of overloaded function not allowed" error
typedef union {
    struct {
        unsigned long LowPart;
        long HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        unsigned long LowPart;
        long HighPart;
    } u;
    utest_int64_t QuadPart;
} utest_large_integer;

UTEST_C_FUNC __declspec(dllimport) int __stdcall QueryPerformanceCounter(
                                                                         utest_large_integer *);
UTEST_C_FUNC __declspec(dllimport) int __stdcall QueryPerformanceFrequency(
                                                                           utest_large_integer *);

#if defined(__MINGW64__) || defined(__MINGW32__)
#pragma GCC diagnostic pop
#endif
#endif

#elif defined(__linux__) \
|| defined(__FreeBSD__) \
|| defined(__OpenBSD__) \
|| defined(__NetBSD__) \
|| defined(__DragonFly__) \
|| defined(__sun__) \
|| defined(__HAIKU__)
/*
   slightly obscure include here - we need to include glibc's features.h, but
   we don't want to just include a header that might not be defined for other
   c libraries like musl. Instead we include limits.h, which we know on all
   glibc distributions includes features.h
*/
#include <limits.h>

#if defined(__GLIBC__) && defined(__GLIBC_MINOR__)
#include <time.h>

#if ((2 < __GLIBC__) || ((2 == __GLIBC__) && (17 <= __GLIBC_MINOR__)))
/* glibc is version 2.17 or above, so we can just use clock_gettime */
#define UTEST_USE_CLOCKGETTIME
#else
#include <sys/syscall.h>
#include <unistd.h>
#endif
#else // Other libc implementations
#include <time.h>
#define UTEST_USE_CLOCKGETTIME
#endif

#elif defined(__APPLE__)
#include <mach/mach_time.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1920)
#define UTEST_PRId64 "I64d"
#define UTEST_PRIu64 "I64u"
#else
#include <inttypes.h>

#define UTEST_PRId64 PRId64
#define UTEST_PRIu64 PRIu64
#endif

#if defined(__cplusplus)
#define UTEST_INLINE inline

#if defined(__clang__)
#define UTEST_INITIALIZER_BEGIN_DISABLE_WARNINGS                               \
_Pragma("clang diagnostic push")                                             \
_Pragma("clang diagnostic ignored \"-Wglobal-constructors\"")

#define UTEST_INITIALIZER_END_DISABLE_WARNINGS _Pragma("clang diagnostic pop")
#else
#define UTEST_INITIALIZER_BEGIN_DISABLE_WARNINGS
#define UTEST_INITIALIZER_END_DISABLE_WARNINGS
#endif

#define UTEST_INITIALIZER(f)                                                   \
struct f##_cpp_struct { f##_cpp_struct(); }; \
UTEST_INITIALIZER_BEGIN_DISABLE_WARNINGS static f##_cpp_struct f##_cpp_global UTEST_INITIALIZER_END_DISABLE_WARNINGS; \
f##_cpp_struct::f##_cpp_struct()
#elif defined(_MSC_VER)
#define UTEST_INLINE __forceinline

#if defined(_WIN64)
#define UTEST_SYMBOL_PREFIX
#else
#define UTEST_SYMBOL_PREFIX "_"
#endif

#if defined(__clang__)
#define UTEST_INITIALIZER_BEGIN_DISABLE_WARNINGS                               \
_Pragma("clang diagnostic push")                                             \
_Pragma("clang diagnostic ignored \"-Wmissing-variable-declarations\"")

#define UTEST_INITIALIZER_END_DISABLE_WARNINGS _Pragma("clang diagnostic pop")
#else
#define UTEST_INITIALIZER_BEGIN_DISABLE_WARNINGS
#define UTEST_INITIALIZER_END_DISABLE_WARNINGS
#endif

#pragma section(".CRT$XCU", read)
#define UTEST_INITIALIZER(f)                                                   \
static void __cdecl f(void);                                                 \
UTEST_INITIALIZER_BEGIN_DISABLE_WARNINGS                                     \
__pragma(comment(linker, "/include:" UTEST_SYMBOL_PREFIX #f "_"))            \
UTEST_C_FUNC __declspec(allocate(".CRT$XCU")) void(__cdecl *             \
f##_)(void) = f;      \
UTEST_INITIALIZER_END_DISABLE_WARNINGS                                       \
static void __cdecl f(void)
#else
#if defined(__linux__)
#if defined(__clang__)
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#endif

#define __STDC_FORMAT_MACROS 1

#if defined(__clang__)
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic pop
#endif
#endif
#endif

#define UTEST_INLINE inline

#define UTEST_INITIALIZER(f)                                                   \
static void f(void) __attribute__((constructor));                            \
static void f(void)
#endif

#if defined(__cplusplus)
#define UTEST_CAST(type, x) static_cast<type>(x)
#define UTEST_PTR_CAST(type, x) reinterpret_cast<type>(x)
#define UTEST_EXTERN extern "C"
#define UTEST_NULL NULL
#else
#define UTEST_CAST(type, x) ((type)(x))
#define UTEST_PTR_CAST(type, x) ((type)(x))
#define UTEST_EXTERN extern
#define UTEST_NULL 0
#endif

#ifdef _MSC_VER
/*
    io.h contains definitions for some structures with natural padding. This is
    uninteresting, but for some reason MSVC's behaviour is to warn about
    including this system header. That *is* interesting
*/
#pragma warning(disable : 4820)
#pragma warning(push, 1)
#include <io.h>
#pragma warning(pop)
#define UTEST_COLOUR_OUTPUT() (_isatty(_fileno(stdout)))
#else
#if  defined(__EMSCRIPTEN__)
#include <emscripten/html5.h>
#define UTEST_COLOUR_OUTPUT() false
#else
#include <unistd.h>
#define UTEST_COLOUR_OUTPUT() (isatty(STDOUT_FILENO))
#endif
#endif

static UTEST_INLINE void *utest_realloc(void *const pointer, size_t new_size) {
    void *const new_pointer = realloc(pointer, new_size);
    
    if (UTEST_NULL == new_pointer) {
        free(new_pointer);
    }
    
    return new_pointer;
}

static UTEST_INLINE utest_int64_t utest_ns(void) {
#if defined(_MSC_VER) || defined(__MINGW64__) || defined(__MINGW32__)
    utest_large_integer counter;
    utest_large_integer frequency;
    QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&frequency);
    return UTEST_CAST(utest_int64_t,
                      (counter.QuadPart * 1000000000) / frequency.QuadPart);
#elif defined(__linux__) && defined(__STRICT_ANSI__)
    return UTEST_CAST(utest_int64_t, clock()) * 1000000000 / CLOCKS_PER_SEC;
#elif defined(__linux__) \
|| defined(__FreeBSD__) \
|| defined(__OpenBSD__) \
|| defined(__NetBSD__) \
|| defined(__DragonFly__) \
|| defined(__sun__) \
|| defined(__HAIKU__)
    struct timespec ts;
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__HAIKU__)
    timespec_get(&ts, TIME_UTC);
#else
    const clockid_t cid = CLOCK_REALTIME;
#if defined(UTEST_USE_CLOCKGETTIME)
    clock_gettime(cid, &ts);
#else
    syscall(SYS_clock_gettime, cid, &ts);
#endif
#endif
    return UTEST_CAST(utest_int64_t, ts.tv_sec) * 1000 * 1000 * 1000 + ts.tv_nsec;
#elif __APPLE__
    return UTEST_CAST(utest_int64_t, mach_absolute_time());
#elif __EMSCRIPTEN__
    return emscripten_performance_now() * 1000000.0;
#else
#error Unsupported platform!
#endif
}

typedef void (*utest_testcase_t)(int *, size_t);

struct utest_test_state_s {
    utest_testcase_t func;
    size_t index;
    char *name;
};

struct utest_state_s {
    struct utest_test_state_s *tests;
    size_t tests_length;
    FILE *output;
};

/* extern to the global state utest needs to execute */
UTEST_EXTERN struct utest_state_s utest_state;

#if defined(_MSC_VER)
#define UTEST_WEAK __forceinline
#else
#define UTEST_WEAK __attribute__((weak))
#endif

#if defined(_MSC_VER)
#define UTEST_UNUSED
#else
#define UTEST_UNUSED __attribute__((unused))
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvariadic-macros"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif
#define UTEST_PRINTF(...)                                                      \
if (utest_state.output) {                                                    \
fprintf(utest_state.output, __VA_ARGS__);                                  \
}                                                                            \
printf(__VA_ARGS__)
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvariadic-macros"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif

#ifdef _MSC_VER
#define UTEST_SNPRINTF(BUFFER, N, ...) _snprintf_s(BUFFER, N, N, __VA_ARGS__)
#else
#define UTEST_SNPRINTF(...) snprintf(__VA_ARGS__)
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#if defined(__cplusplus)
/* if we are using c++ we can use overloaded methods (its in the language) */
#define UTEST_OVERLOADABLE
#elif defined(__clang__)
/* otherwise, if we are using clang with c - use the overloadable attribute */
#define UTEST_OVERLOADABLE __attribute__((overloadable))
#endif

#if defined(UTEST_OVERLOADABLE)
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(float f);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(float f) {
    UTEST_PRINTF("%f", UTEST_CAST(double, f));
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(double d);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(double d) {
    UTEST_PRINTF("%f", d);
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long double d);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long double d) {
    UTEST_PRINTF("%Lf", d);
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(int i);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(int i) {
    UTEST_PRINTF("%d", i);
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(unsigned int i);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(unsigned int i) {
    UTEST_PRINTF("%u", i);
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long int i);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long int i) {
    UTEST_PRINTF("%ld", i);
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long unsigned int i);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long unsigned int i) {
    UTEST_PRINTF("%lu", i);
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(const void *p);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(const void *p) {
    UTEST_PRINTF("%p", p);
}

/*
   long long is a c++11 extension
*/
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) ||              \
defined(__cplusplus) && (__cplusplus >= 201103L)

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long long int i);
UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long long int i) {
    UTEST_PRINTF("%lld", i);
}

UTEST_WEAK UTEST_OVERLOADABLE void utest_type_printer(long long unsigned int i);
UTEST_WEAK UTEST_OVERLOADABLE void
utest_type_printer(long long unsigned int i) {
    UTEST_PRINTF("%llu", i);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#define utest_type_printer(val)                                                \
UTEST_PRINTF(_Generic((val), signed char                                     \
: "%d", unsigned char                                  \
: "%u", short                                          \
: "%d", unsigned short                                 \
: "%u", int                                            \
: "%d", long                                           \
: "%ld", long long                                     \
: "%lld", unsigned                                     \
: "%u", unsigned long                                  \
: "%lu", unsigned long long                            \
: "%llu", float                                        \
: "%f", double                                         \
: "%f", long double                                    \
: "%Lf", default                                       \
: _Generic((val - val), ptrdiff_t                      \
: "%p", default                             \
: "undef")),                                \
(val))
#else
/*
   we don't have the ability to print the values we got, so we create a macro
   to tell our users we can't do anything fancy
*/
#define utest_type_printer(...) UTEST_PRINTF("undef")
#endif

#ifdef _MSC_VER
#define UTEST_SURPRESS_WARNING_BEGIN                                           \
__pragma(warning(push)) __pragma(warning(disable : 4127))
#define UTEST_SURPRESS_WARNING_END __pragma(warning(pop))
#else
#define UTEST_SURPRESS_WARNING_BEGIN
#define UTEST_SURPRESS_WARNING_END
#endif

#if defined(__cplusplus) && (__cplusplus >= 201103L)
#define UTEST_AUTO(x) auto
#elif !defined(__cplusplus)

#if defined(__clang__)
/* clang-format off */
/* had to disable clang-format here because it malforms the pragmas */
#define UTEST_AUTO(x)                                                          \
_Pragma("clang diagnostic push")                                             \
_Pragma("clang diagnostic ignored \"-Wgnu-auto-type\"") __auto_type      \
_Pragma("clang diagnostic pop")
/* clang-format on */
#else
#define UTEST_AUTO(x) __typeof__(x + 0)
#endif

#else
#define UTEST_AUTO(x) typeof(x + 0)
#endif

#if defined(__clang__)
#define UTEST_STRNCMP(x, y, size)                                              \
_Pragma("clang diagnostic push")                                             \
_Pragma("clang diagnostic ignored \"-Wdisabled-macro-expansion\"")       \
strncmp(x, y, size) _Pragma("clang diagnostic pop")
#else
#define UTEST_STRNCMP(x, y, size) strncmp(x, y, size)
#endif

#if defined(__clang__)
#define UTEST_EXPECT(x, y, cond)                                               \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
_Pragma("clang diagnostic push")                                           \
_Pragma("clang diagnostic ignored \"-Wlanguage-extension-token\"")     \
_Pragma("clang diagnostic ignored \"-Wc++98-compat-pedantic\"")    \
_Pragma("clang diagnostic ignored \"-Wfloat-equal\"")          \
UTEST_AUTO(x) xEval = (x);                                 \
UTEST_AUTO(y) yEval = (y);                                                 \
if (!((xEval)cond(yEval))) {                                               \
_Pragma("clang diagnostic pop")                                          \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                \
UTEST_PRINTF("  Expected : ");                                           \
utest_type_printer(xEval);                                               \
UTEST_PRINTF("\n");                                                      \
UTEST_PRINTF("    Actual : ");                                           \
utest_type_printer(yEval);                                               \
UTEST_PRINTF("\n");                                                      \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END
#elif defined(__GNUC__)
#define UTEST_EXPECT(x, y, cond)                                               \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
UTEST_AUTO(x) xEval = (x);                                                 \
UTEST_AUTO(y) yEval = (y);                                                 \
if (!((xEval)cond(yEval))) {                                               \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : ");                                           \
utest_type_printer(xEval);                                               \
UTEST_PRINTF("\n");                                                      \
UTEST_PRINTF("    Actual : ");                                           \
utest_type_printer(yEval);                                               \
UTEST_PRINTF("\n");                                                      \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END
#else
#define UTEST_EXPECT(x, y, cond)                                               \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (!((x)cond(y))) {                                                       \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END
#endif

#define EXPECT_TRUE(x)                                                         \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (!(x)) {                                                                \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : true\n");                                     \
UTEST_PRINTF("    Actual : %s\n", (x) ? "true" : "false");               \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define EXPECT_FALSE(x)                                                        \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (x) {                                                                   \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : false\n");                                    \
UTEST_PRINTF("    Actual : %s\n", (x) ? "true" : "false");               \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define EXPECT_EQ(x, y) UTEST_EXPECT(x, y, ==)
#define EXPECT_NE(x, y) UTEST_EXPECT(x, y, !=)
#define EXPECT_LT(x, y) UTEST_EXPECT(x, y, <)
#define EXPECT_LE(x, y) UTEST_EXPECT(x, y, <=)
#define EXPECT_GT(x, y) UTEST_EXPECT(x, y, >)
#define EXPECT_GE(x, y) UTEST_EXPECT(x, y, >=)

#define EXPECT_STREQ(x, y)                                                     \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 != strcmp(x, y)) {                                                   \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%s\"\n", x);                                \
UTEST_PRINTF("    Actual : \"%s\"\n", y);                                \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define EXPECT_STRNE(x, y)                                                     \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 == strcmp(x, y)) {                                                   \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%s\"\n", x);                                \
UTEST_PRINTF("    Actual : \"%s\"\n", y);                                \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define EXPECT_STRNEQ(x, y, n)                                                 \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 != UTEST_STRNCMP(x, y, n)) {                                         \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%.*s\"\n", UTEST_CAST(int, n), x);          \
UTEST_PRINTF("    Actual : \"%.*s\"\n", UTEST_CAST(int, n), y);          \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define EXPECT_STRNNE(x, y, n)                                                 \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 == UTEST_STRNCMP(x, y, n)) {                                         \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%.*s\"\n", UTEST_CAST(int, n), x);          \
UTEST_PRINTF("    Actual : \"%.*s\"\n", UTEST_CAST(int, n), y);          \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define EXPECT_NEAR(x, y, epsilon)                                             \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (utest_fabs(UTEST_CAST(double, x) - UTEST_CAST(double, y)) >            \
UTEST_CAST(double, epsilon)) {                                         \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : %f\n", UTEST_CAST(double, x));                \
UTEST_PRINTF("    Actual : %f\n", UTEST_CAST(double, y));                \
*utest_result = 1;                                                       \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#if defined(__clang__)
#define UTEST_ASSERT(x, y, cond)                                               \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
_Pragma("clang diagnostic push")                                           \
_Pragma("clang diagnostic ignored \"-Wlanguage-extension-token\"")     \
_Pragma("clang diagnostic ignored \"-Wc++98-compat-pedantic\"")    \
_Pragma("clang diagnostic ignored \"-Wfloat-equal\"")          \
UTEST_AUTO(x) xEval = (x);                                 \
UTEST_AUTO(y) yEval = (y);                                                 \
if (!((xEval)cond(yEval))) {                                               \
_Pragma("clang diagnostic pop")                                          \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                \
UTEST_PRINTF("  Expected : ");                                           \
utest_type_printer(xEval);                                               \
UTEST_PRINTF("\n");                                                      \
UTEST_PRINTF("    Actual : ");                                           \
utest_type_printer(yEval);                                               \
UTEST_PRINTF("\n");                                                      \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END
#elif defined(__GNUC__)
#define UTEST_ASSERT(x, y, cond)                                               \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
UTEST_AUTO(x) xEval = (x);                                                 \
UTEST_AUTO(y) yEval = (y);                                                 \
if (!((xEval)cond(yEval))) {                                               \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : ");                                           \
utest_type_printer(xEval);                                               \
UTEST_PRINTF("\n");                                                      \
UTEST_PRINTF("    Actual : ");                                           \
utest_type_printer(yEval);                                               \
UTEST_PRINTF("\n");                                                      \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END
#else
#define UTEST_ASSERT(x, y, cond)                                               \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (!((x)cond(y))) {                                                       \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END
#endif

#define ASSERT_TRUE(x)                                                         \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (!(x)) {                                                                \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : true\n");                                     \
UTEST_PRINTF("    Actual : %s\n", (x) ? "true" : "false");               \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define ASSERT_FALSE(x)                                                        \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (x) {                                                                   \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : false\n");                                    \
UTEST_PRINTF("    Actual : %s\n", (x) ? "true" : "false");               \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define ASSERT_EQ(x, y) UTEST_ASSERT(x, y, ==)
#define ASSERT_NE(x, y) UTEST_ASSERT(x, y, !=)
#define ASSERT_LT(x, y) UTEST_ASSERT(x, y, <)
#define ASSERT_LE(x, y) UTEST_ASSERT(x, y, <=)
#define ASSERT_GT(x, y) UTEST_ASSERT(x, y, >)
#define ASSERT_GE(x, y) UTEST_ASSERT(x, y, >=)

#define ASSERT_STREQ(x, y)                                                     \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 != strcmp(x, y)) {                                                   \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%s\"\n", x);                                \
UTEST_PRINTF("    Actual : \"%s\"\n", y);                                \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define ASSERT_STRNE(x, y)                                                     \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 == strcmp(x, y)) {                                                   \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%s\"\n", x);                                \
UTEST_PRINTF("    Actual : \"%s\"\n", y);                                \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define ASSERT_STRNEQ(x, y, n)                                                 \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 != UTEST_STRNCMP(x, y, n)) {                                         \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%.*s\"\n", UTEST_CAST(int, n), x);          \
UTEST_PRINTF("    Actual : \"%.*s\"\n", UTEST_CAST(int, n), y);          \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define ASSERT_STRNNE(x, y, n)                                                 \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (0 == UTEST_STRNCMP(x, y, n)) {                                         \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : \"%.*s\"\n", UTEST_CAST(int, n), x);          \
UTEST_PRINTF("    Actual : \"%.*s\"\n", UTEST_CAST(int, n), y);          \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define ASSERT_NEAR(x, y, epsilon)                                             \
UTEST_SURPRESS_WARNING_BEGIN do {                                            \
if (utest_fabs(UTEST_CAST(double, x) - UTEST_CAST(double, y)) >            \
UTEST_CAST(double, epsilon)) {                                         \
UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
UTEST_PRINTF("  Expected : %f\n", UTEST_CAST(double, x));                \
UTEST_PRINTF("    Actual : %f\n", UTEST_CAST(double, y));                \
*utest_result = 1;                                                       \
return;                                                                  \
}                                                                          \
}                                                                            \
while (0)                                                                    \
UTEST_SURPRESS_WARNING_END

#define UTEST(SET, NAME)                                                       \
UTEST_EXTERN struct utest_state_s utest_state;                               \
static void utest_run_##SET##_##NAME(int *utest_result);                     \
static void utest_##SET##_##NAME(int *utest_result, size_t utest_index) {    \
(void)utest_index;                                                         \
utest_run_##SET##_##NAME(utest_result);                                    \
}                                                                            \
UTEST_INITIALIZER(utest_register_##SET##_##NAME) {                           \
const size_t index = utest_state.tests_length++;                           \
const char *name_part = #SET "." #NAME;                                    \
const size_t name_size = strlen(name_part) + 1;                            \
char *name = UTEST_PTR_CAST(char *, malloc(name_size));                    \
utest_state.tests = UTEST_PTR_CAST(                                        \
struct utest_test_state_s *,                                           \
utest_realloc(UTEST_PTR_CAST(void *, utest_state.tests),               \
sizeof(struct utest_test_state_s) *                      \
utest_state.tests_length));                          \
if (utest_state.tests) {                                                   \
utest_state.tests[index].func = &utest_##SET##_##NAME;                   \
utest_state.tests[index].name = name;                                    \
utest_state.tests[index].index = 0;                                      \
}                                                                          \
UTEST_SNPRINTF(name, name_size, "%s", name_part);                          \
}                                                                            \
void utest_run_##SET##_##NAME(int *utest_result)

#define UTEST_F_SETUP(FIXTURE)                                                 \
static void utest_f_setup_##FIXTURE(int *utest_result,                       \
struct FIXTURE *utest_fixture)

#define UTEST_F_TEARDOWN(FIXTURE)                                              \
static void utest_f_teardown_##FIXTURE(int *utest_result,                    \
struct FIXTURE *utest_fixture)

#define UTEST_F(FIXTURE, NAME)                                                 \
UTEST_EXTERN struct utest_state_s utest_state;                               \
static void utest_f_setup_##FIXTURE(int *, struct FIXTURE *);                \
static void utest_f_teardown_##FIXTURE(int *, struct FIXTURE *);             \
static void utest_run_##FIXTURE##_##NAME(int *, struct FIXTURE *);           \
static void utest_f_##FIXTURE##_##NAME(int *utest_result,                    \
size_t utest_index) {                 \
struct FIXTURE fixture;                                                    \
(void)utest_index;                                                         \
memset(&fixture, 0, sizeof(fixture));                                      \
utest_f_setup_##FIXTURE(utest_result, &fixture);                           \
if (0 != *utest_result) {                                                  \
return;                                                                  \
}                                                                          \
utest_run_##FIXTURE##_##NAME(utest_result, &fixture);                      \
utest_f_teardown_##FIXTURE(utest_result, &fixture);                        \
}                                                                            \
UTEST_INITIALIZER(utest_register_##FIXTURE##_##NAME) {                       \
const size_t index = utest_state.tests_length++;                           \
const char *name_part = #FIXTURE "." #NAME;                                \
const size_t name_size = strlen(name_part) + 1;                            \
char *name = UTEST_PTR_CAST(char *, malloc(name_size));                    \
utest_state.tests = UTEST_PTR_CAST(                                        \
struct utest_test_state_s *,                                           \
utest_realloc(UTEST_PTR_CAST(void *, utest_state.tests),               \
sizeof(struct utest_test_state_s) *                      \
utest_state.tests_length));                          \
utest_state.tests[index].func = &utest_f_##FIXTURE##_##NAME;               \
utest_state.tests[index].name = name;                                      \
UTEST_SNPRINTF(name, name_size, "%s", name_part);                          \
}                                                                            \
void utest_run_##FIXTURE##_##NAME(int *utest_result,                         \
struct FIXTURE *utest_fixture)

#define UTEST_I_SETUP(FIXTURE)                                                 \
static void utest_i_setup_##FIXTURE(                                         \
int *utest_result, struct FIXTURE *utest_fixture, size_t utest_index)

#define UTEST_I_TEARDOWN(FIXTURE)                                              \
static void utest_i_teardown_##FIXTURE(                                      \
int *utest_result, struct FIXTURE *utest_fixture, size_t utest_index)

#define UTEST_I(FIXTURE, NAME, INDEX)                                          \
UTEST_EXTERN struct utest_state_s utest_state;                               \
static void utest_run_##FIXTURE##_##NAME##_##INDEX(int *, struct FIXTURE *); \
static void utest_i_##FIXTURE##_##NAME##_##INDEX(int *utest_result,          \
size_t index) {             \
struct FIXTURE fixture;                                                    \
memset(&fixture, 0, sizeof(fixture));                                      \
utest_i_setup_##FIXTURE(utest_result, &fixture, index);                    \
if (0 != *utest_result) {                                                  \
return;                                                                  \
}                                                                          \
utest_run_##FIXTURE##_##NAME##_##INDEX(utest_result, &fixture);            \
utest_i_teardown_##FIXTURE(utest_result, &fixture, index);                 \
}                                                                            \
UTEST_INITIALIZER(utest_register_##FIXTURE##_##NAME##_##INDEX) {             \
size_t i;                                                                  \
utest_uint64_t iUp;                                                        \
for (i = 0; i < (INDEX); i++) {                                            \
const size_t index = utest_state.tests_length++;                         \
const char *name_part = #FIXTURE "." #NAME;                              \
const size_t name_size = strlen(name_part) + 32;                         \
char *name = UTEST_PTR_CAST(char *, malloc(name_size));                  \
utest_state.tests = UTEST_PTR_CAST(                                      \
struct utest_test_state_s *,                                         \
utest_realloc(UTEST_PTR_CAST(void *, utest_state.tests),             \
sizeof(struct utest_test_state_s) *                    \
utest_state.tests_length));                        \
utest_state.tests[index].func = &utest_i_##FIXTURE##_##NAME##_##INDEX;   \
utest_state.tests[index].index = i;                                      \
utest_state.tests[index].name = name;                                    \
iUp = UTEST_CAST(utest_uint64_t, i);                                     \
UTEST_SNPRINTF(name, name_size, "%s/%" UTEST_PRIu64, name_part, iUp);    \
}                                                                          \
}                                                                            \
void utest_run_##FIXTURE##_##NAME##_##INDEX(int *utest_result,               \
struct FIXTURE *utest_fixture)

UTEST_WEAK
double utest_fabs(double d);
UTEST_WEAK
double utest_fabs(double d) {
    union {
        double d;
        utest_uint64_t u;
    } both;
    both.d = d;
    both.u &= 0x7fffffffffffffffu;
    return both.d;
}

UTEST_WEAK
int utest_should_filter_test(const char *filter, const char *testcase);
UTEST_WEAK int utest_should_filter_test(const char *filter,
                                        const char *testcase) {
    if (filter) {
        const char *filter_cur = filter;
        const char *testcase_cur = testcase;
        const char *filter_wildcard = UTEST_NULL;
        
        while (('\0' != *filter_cur) && ('\0' != *testcase_cur)) {
            if ('*' == *filter_cur) {
                /* store the position of the wildcard */
                filter_wildcard = filter_cur;
                
                /* skip the wildcard character */
                filter_cur++;
                
                while (('\0' != *filter_cur) && ('\0' != *testcase_cur)) {
                    if ('*' == *filter_cur) {
                        /*
                           we found another wildcard (filter is something like *foo*) so we
                           exit the current loop, and return to the parent loop to handle
                           the wildcard case
                        */
                        break;
                    } else if (*filter_cur != *testcase_cur) {
                        /* otherwise our filter didn't match, so reset it */
                        filter_cur = filter_wildcard;
                    }
                    
                    /* move testcase along */
                    testcase_cur++;
                    
                    /* move filter along */
                    filter_cur++;
                }
                
                if (('\0' == *filter_cur) && ('\0' == *testcase_cur)) {
                    return 0;
                }
                
                /* if the testcase has been exhausted, we don't have a match! */
                if ('\0' == *testcase_cur) {
                    return 1;
                }
            } else {
                if (*testcase_cur != *filter_cur) {
                    /* test case doesn't match filter */
                    return 1;
                } else {
                    /* move our filter and testcase forward */
                    testcase_cur++;
                    filter_cur++;
                }
            }
        }
        
        if (('\0' != *filter_cur) ||
            (('\0' != *testcase_cur) &&
             ((filter == filter_cur) || ('*' != filter_cur[-1])))) {
            /* we have a mismatch! */
            return 1;
        }
    }
    
    return 0;
}

static UTEST_INLINE FILE *utest_fopen(const char *filename, const char *mode) {
#ifdef _MSC_VER
    FILE *file;
    if (0 == fopen_s(&file, filename, mode)) {
        return file;
    } else {
        return UTEST_NULL;
    }
#else
    return fopen(filename, mode);
#endif
}

static UTEST_INLINE int utest_main(int argc, const char *const argv[]);
int utest_main(int argc, const char *const argv[]) {
    utest_uint64_t failed = 0;
    size_t index = 0;
    size_t *failed_testcases = UTEST_NULL;
    size_t failed_testcases_length = 0;
    const char *filter = UTEST_NULL;
    utest_uint64_t ran_tests = 0;
    int enable_mixed_units = 0;
    int random_order = 0;
    utest_uint32_t seed = 0;
    
    enum colours { RESET, GREEN, RED };
    
    const int use_colours = UTEST_COLOUR_OUTPUT();
    const char *colours[] = {"\033[0m", "\033[32m", "\033[31m"};
    
    if (!use_colours) {
        for (index = 0; index < sizeof colours / sizeof colours[0]; index++) {
            colours[index] = "";
        }
    }
    /* loop through all arguments looking for our options */
    for (index = 1; index < UTEST_CAST(size_t, argc); index++) {
        /* Informational switches */
        const char help_str[] = "--help";
        const char list_str[] = "--list-tests";
        /* Test config switches */
        const char filter_str[] = "--filter=";
        const char output_str[] = "--output=";
        const char enable_mixed_units_str[] = "--enable-mixed-units";
        const char random_order_str[] = "--random-order";
        const char random_order_with_seed_str[] = "--random-order=";
        
        if (0 == UTEST_STRNCMP(argv[index], help_str, strlen(help_str))) {
            printf("utest.h - the single file unit testing solution for C/C++!\n"
                   "Command line Options:\n"
                   "  --help                  Show this message and exit.\n"
                   "  --filter=<filter>       Filter the test cases to run (EG. "
                   "MyTest*.a would run MyTestCase.a but not MyTestCase.b).\n"
                   "  --list-tests            List testnames, one per line. Output "
                   "names can be passed to --filter.\n");
            printf("  --output=<output>       Output an xunit XML file to the file "
                   "specified in <output>.\n"
                   "  --enable-mixed-units    Enable the per-test output to contain "
                   "mixed units (s/ms/us/ns).\n"
                   "  --random-order[=<seed>] Randomize the order that the tests are "
                   "ran in. If the optional <seed> argument is not provided, then a "
                   "random starting seed is used.\n");
            goto cleanup;
        } else if (0 ==
                   UTEST_STRNCMP(argv[index], filter_str, strlen(filter_str))) {
            /* user wants to filter what test cases run! */
            filter = argv[index] + strlen(filter_str);
        } else if (0 ==
                   UTEST_STRNCMP(argv[index], output_str, strlen(output_str))) {
            utest_state.output = utest_fopen(argv[index] + strlen(output_str), "w+");
        } else if (0 == UTEST_STRNCMP(argv[index], list_str, strlen(list_str))) {
            for (index = 0; index < utest_state.tests_length; index++) {
                UTEST_PRINTF("%s\n", utest_state.tests[index].name);
            }
            /* when printing the test list, don't actually run the tests */
            return 0;
        } else if (0 == UTEST_STRNCMP(argv[index], enable_mixed_units_str,
                                      strlen(enable_mixed_units_str))) {
            enable_mixed_units = 1;
        } else if (0 == UTEST_STRNCMP(argv[index], random_order_with_seed_str,
                                      strlen(random_order_with_seed_str))) {
            seed =
                UTEST_CAST(utest_uint32_t,
                           strtoul(argv[index] + strlen(random_order_with_seed_str),
                                   UTEST_NULL, 10));
            random_order = 1;
        } else if (0 == UTEST_STRNCMP(argv[index], random_order_str,
                                      strlen(random_order_str))) {
            const utest_int64_t ns = utest_ns();
            
            // Some really poor pseudo-random using the current time. I do this
            // because I really want to avoid using C's rand() because that'd mean our
            // random would be affected by any srand() usage by the user (which I
            // don't want).
            seed = UTEST_CAST(utest_uint32_t, ns >> 32) * 31 +
                UTEST_CAST(utest_uint32_t, ns & 0xffffffff);
            random_order = 1;
        }
    }
    
    if (random_order) {
        // Use Fisher-Yates with the Durstenfield's version to randomly re-order the
        // tests.
        for (index = utest_state.tests_length; index > 1; index--) {
            // For the random order we'll use PCG.
            const utest_uint32_t state = seed;
            const utest_uint32_t word =
            ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
            const utest_uint32_t next = ((word >> 22u) ^ word) % index;
            
            // Swap the randomly chosen element into the last location.
            const struct utest_test_state_s copy = utest_state.tests[index - 1];
            utest_state.tests[index - 1] = utest_state.tests[next];
            utest_state.tests[next] = copy;
            
            // Move the seed onwards.
            seed = seed * 747796405u + 2891336453u;
        }
    }
    
    for (index = 0; index < utest_state.tests_length; index++) {
        if (utest_should_filter_test(filter, utest_state.tests[index].name)) {
            continue;
        }
        
        ran_tests++;
    }
    
    printf("%s[==========]%s Running %" UTEST_PRIu64 " test cases.\n",
           colours[GREEN], colours[RESET], UTEST_CAST(utest_uint64_t, ran_tests));
    
    if (utest_state.output) {
        fprintf(utest_state.output, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        fprintf(utest_state.output,
                "<testsuites tests=\"%" UTEST_PRIu64 "\" name=\"All\">\n",
                UTEST_CAST(utest_uint64_t, ran_tests));
        fprintf(utest_state.output,
                "<testsuite name=\"Tests\" tests=\"%" UTEST_PRIu64 "\">\n",
                UTEST_CAST(utest_uint64_t, ran_tests));
    }
    
    for (index = 0; index < utest_state.tests_length; index++) {
        int result = 0;
        utest_int64_t ns = 0;
        
        if (utest_should_filter_test(filter, utest_state.tests[index].name)) {
            continue;
        }
        
        printf("%s[ RUN      ]%s %s\n", colours[GREEN], colours[RESET],
               utest_state.tests[index].name);
        
        if (utest_state.output) {
            fprintf(utest_state.output, "<testcase name=\"%s\">",
                    utest_state.tests[index].name);
        }
        
        ns = utest_ns();
        errno = 0;
        utest_state.tests[index].func(&result, utest_state.tests[index].index);
        ns = utest_ns() - ns;
        
        if (utest_state.output) {
            fprintf(utest_state.output, "</testcase>\n");
        }
        
        // Record the failing test.
        if (0 != result) {
            const size_t failed_testcase_index = failed_testcases_length++;
            failed_testcases = UTEST_PTR_CAST(
                                              size_t *, utest_realloc(UTEST_PTR_CAST(void *, failed_testcases),
                                                                      sizeof(size_t) * failed_testcases_length));
            if (UTEST_NULL != failed_testcases) {
                failed_testcases[failed_testcase_index] = index;
            }
            failed++;
        }
        
        {
            const char *const units[] = {"ns", "us", "ms", "s", UTEST_NULL};
            unsigned int unit_index = 0;
            utest_int64_t time = ns;
            
            if (enable_mixed_units) {
                for (unit_index = 0; UTEST_NULL != units[unit_index]; unit_index++) {
                    if (10000 > time) {
                        break;
                    }
                    
                    time /= 1000;
                }
            }
            
            if (0 != result) {
                printf("%s[  FAILED  ]%s %s (%" UTEST_PRId64 "%s)\n", colours[RED],
                       colours[RESET], utest_state.tests[index].name, time,
                       units[unit_index]);
            } else {
                printf("%s[       OK ]%s %s (%" UTEST_PRId64 "%s)\n", colours[GREEN],
                       colours[RESET], utest_state.tests[index].name, time,
                       units[unit_index]);
            }
        }
    }
    
    printf("%s[==========]%s %" UTEST_PRIu64 " test cases ran.\n", colours[GREEN],
           colours[RESET], ran_tests);
    printf("%s[  PASSED  ]%s %" UTEST_PRIu64 " tests.\n", colours[GREEN],
           colours[RESET], ran_tests - failed);
    
    if (0 != failed) {
        printf("%s[  FAILED  ]%s %" UTEST_PRIu64 " tests, listed below:\n",
               colours[RED], colours[RESET], failed);
        for (index = 0; index < failed_testcases_length; index++) {
            printf("%s[  FAILED  ]%s %s\n", colours[RED], colours[RESET],
                   utest_state.tests[failed_testcases[index]].name);
        }
    }
    
    if (utest_state.output) {
        fprintf(utest_state.output, "</testsuite>\n</testsuites>\n");
    }
    
    cleanup:
    for (index = 0; index < utest_state.tests_length; index++) {
        free(UTEST_PTR_CAST(void *, utest_state.tests[index].name));
    }
    
    free(UTEST_PTR_CAST(void *, failed_testcases));
    free(UTEST_PTR_CAST(void *, utest_state.tests));
    
    if (utest_state.output) {
        fclose(utest_state.output);
    }
    
    return UTEST_CAST(int, failed);
}

/*
   we need, in exactly one source file, define the global struct that will hold
   the data we need to run utest. This macro allows the user to declare the
   data without having to use the UTEST_MAIN macro, thus allowing them to write
   their own main() function.
*/
#define UTEST_STATE() struct utest_state_s utest_state = {0, 0, 0}

/*
   define a main() function to call into utest.h and start executing tests! A
   user can optionally not use this macro, and instead define their own main()
   function and manually call utest_main. The user must, in exactly one source
   file, use the UTEST_STATE macro to declare a global struct variable that
   utest requires.
*/
#define UTEST_MAIN()                                                           \
UTEST_STATE();                                                               \
int main(int argc, const char *const argv[]) {                               \
return utest_main(argc, argv);                                             \
}

#endif /* SHEREDOM_UTEST_H_INCLUDED */

UTEST_MAIN();

#endif // AK_MATH_TESTS