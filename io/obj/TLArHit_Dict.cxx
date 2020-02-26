// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TLArHit_Dict

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
#include "TLArHit.hxx"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TLArHit(void *p = 0);
   static void *newArray_TLArHit(Long_t size, void *p);
   static void delete_TLArHit(void *p);
   static void deleteArray_TLArHit(void *p);
   static void destruct_TLArHit(void *p);
   static void streamer_TLArHit(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TLArHit*)
   {
      ::TLArHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TLArHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TLArHit", ::TLArHit::Class_Version(), "TLArHit.hxx", 13,
                  typeid(::TLArHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TLArHit::Dictionary, isa_proxy, 16,
                  sizeof(::TLArHit) );
      instance.SetNew(&new_TLArHit);
      instance.SetNewArray(&newArray_TLArHit);
      instance.SetDelete(&delete_TLArHit);
      instance.SetDeleteArray(&deleteArray_TLArHit);
      instance.SetDestructor(&destruct_TLArHit);
      instance.SetStreamerFunc(&streamer_TLArHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TLArHit*)
   {
      return GenerateInitInstanceLocal((::TLArHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TLArHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TLArHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TLArHit::Class_Name()
{
   return "TLArHit";
}

//______________________________________________________________________________
const char *TLArHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TLArHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TLArHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TLArHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TLArHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TLArHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TLArHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TLArHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TLArHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class TLArHit.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> edep;
      R__b >> PE;
      posEnd.Streamer(R__b);
      posStart.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TLArHit::IsA());
   } else {
      R__c = R__b.WriteVersion(TLArHit::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << edep;
      R__b << PE;
      posEnd.Streamer(R__b);
      posStart.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TLArHit(void *p) {
      return  p ? new(p) ::TLArHit : new ::TLArHit;
   }
   static void *newArray_TLArHit(Long_t nElements, void *p) {
      return p ? new(p) ::TLArHit[nElements] : new ::TLArHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_TLArHit(void *p) {
      delete ((::TLArHit*)p);
   }
   static void deleteArray_TLArHit(void *p) {
      delete [] ((::TLArHit*)p);
   }
   static void destruct_TLArHit(void *p) {
      typedef ::TLArHit current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TLArHit(TBuffer &buf, void *obj) {
      ((::TLArHit*)obj)->::TLArHit::Streamer(buf);
   }
} // end of namespace ROOT for class ::TLArHit

namespace {
  void TriggerDictionaryInitialization_TLArHit_Dict_Impl() {
    static const char* headers[] = {
"TLArHit.hxx",
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
#line 1 "TLArHit_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TLArHit.hxx")))  TLArHit;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TLArHit_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TLArHit.hxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TLArHit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TLArHit_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TLArHit_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TLArHit_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TLArHit_Dict() {
  TriggerDictionaryInitialization_TLArHit_Dict_Impl();
}
