#ifndef HG_UT_H
#define HG_UT_H

#include <cstdint>

#define UAssert( expression ) UOrigAssert(__FILE__, __LINE__, expression)
#define TSTFUN(f) f, #f
typedef void voidfunc_t();
extern void UOrigAssert(const char* filename, uint32_t linenumber, bool value);
extern void URegister(
        voidfunc_t* setup, voidfunc_t* teardown, voidfunc_t* test,
        const char* function_name, const char* label);

#endif /* HG_UT_H */
