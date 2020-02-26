// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TGeHit_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TGeHit.hxx"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TGeHit(void *p = 0);
   static void *newArray_TGeHit(Long_t size, void *p);
   static void delete_TGeHit(void *p);
   static void deleteArray_TGeHit(void *p);
   static void destruct_TGeHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TGeHit*)
   {
      ::TGeHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TGeHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TGeHit", ::TGeHit::Class_Version(), "TGeHit.hxx", 13,
                  typeid(::TGeHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TGeHit::Dictionary, isa_proxy, 4,
                  sizeof(::TGeHit) );
      instance.SetNew(&new_TGeHit);
      instance.SetNewArray(&newArray_TGeHit);
      instance.SetDelete(&delete_TGeHit);
      instance.SetDeleteArray(&deleteArray_TGeHit);
      instance.SetDestructor(&destruct_TGeHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TGeHit*)
   {
      return GenerateInitInstanceLocal((::TGeHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TGeHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TGeHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TGeHit::Class_Name()
{
   return "TGeHit";
}

//______________________________________________________________________________
const char *TGeHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGeHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TGeHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGeHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TGeHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGeHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TGeHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGeHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TGeHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class TGeHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TGeHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(TGeHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TGeHit(void *p) {
      return  p ? new(p) ::TGeHit : new ::TGeHit;
   }
   static void *newArray_TGeHit(Long_t nElements, void *p) {
      return p ? new(p) ::TGeHit[nElements] : new ::TGeHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_TGeHit(void *p) {
      delete ((::TGeHit*)p);
   }
   static void deleteArray_TGeHit(void *p) {
      delete [] ((::TGeHit*)p);
   }
   static void destruct_TGeHit(void *p) {
      typedef ::TGeHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TGeHit

namespace {
  void TriggerDictionaryInitialization_TGeHit_Dict_Impl() {
    static const char* headers[] = {
"TGeHit.hxx",
0
    };
    static const char* includePaths[] = {
"/usr/local/root/include",
"/.",
"/home/admin/root-6.14.06/include",
"/home/gold/legend/MaGeLAr/io/obj/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TGeHit_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TGeHit.hxx")))  TGeHit;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TGeHit_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TGeHit.hxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TGeHit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TGeHit_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TGeHit_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TGeHit_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TGeHit_Dict() {
  TriggerDictionaryInitialization_TGeHit_Dict_Impl();
}
