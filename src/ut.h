#ifndef HG_UT_H
#define HG_UT_H

#define UAssert( expression ) UOrigAssert(__FILE__, __LINE__, expression)
#define TSTFUN(f) f, #f
typedef void voidfunc_t(void);
extern void UOrigAssert(char* filename, uint32_t linenumber, bool value);
extern void URegister(
        voidfunc_t* setup, voidfunc_t* teardown, voidfunc_t* test,
        const char* function_name, const char* label);

#endif /* HG_UT_H */
