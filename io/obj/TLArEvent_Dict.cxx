// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TLArEvent_Dict

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
#include "TLArEvent.hxx"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TLArEvent(void *p = 0);
   static void *newArray_TLArEvent(Long_t size, void *p);
   static void delete_TLArEvent(void *p);
   static void deleteArray_TLArEvent(void *p);
   static void destruct_TLArEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TLArEvent*)
   {
      ::TLArEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TLArEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TLArEvent", ::TLArEvent::Class_Version(), "TLArEvent.hxx", 17,
                  typeid(::TLArEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TLArEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TLArEvent) );
      instance.SetNew(&new_TLArEvent);
      instance.SetNewArray(&newArray_TLArEvent);
      instance.SetDelete(&delete_TLArEvent);
      instance.SetDeleteArray(&deleteArray_TLArEvent);
      instance.SetDestructor(&destruct_TLArEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TLArEvent*)
   {
      return GenerateInitInstanceLocal((::TLArEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TLArEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TLArEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TLArEvent::Class_Name()
{
   return "TLArEvent";
}

//______________________________________________________________________________
const char *TLArEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TLArEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TLArEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TLArEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TLArEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TLArEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TLArEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TLArEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TLArEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TLArEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TLArEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TLArEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TLArEvent(void *p) {
      return  p ? new(p) ::TLArEvent : new ::TLArEvent;
   }
   static void *newArray_TLArEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TLArEvent[nElements] : new ::TLArEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TLArEvent(void *p) {
      delete ((::TLArEvent*)p);
   }
   static void deleteArray_TLArEvent(void *p) {
      delete [] ((::TLArEvent*)p);
   }
   static void destruct_TLArEvent(void *p) {
      typedef ::TLArEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TLArEvent

namespace ROOT {
   static TClass *vectorlETLArHitgR_Dictionary();
   static void vectorlETLArHitgR_TClassManip(TClass*);
   static void *new_vectorlETLArHitgR(void *p = 0);
   static void *newArray_vectorlETLArHitgR(Long_t size, void *p);
   static void delete_vectorlETLArHitgR(void *p);
   static void deleteArray_vectorlETLArHitgR(void *p);
   static void destruct_vectorlETLArHitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TLArHit>*)
   {
      vector<TLArHit> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TLArHit>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TLArHit>", -2, "vector", 210,
                  typeid(vector<TLArHit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETLArHitgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TLArHit>) );
      instance.SetNew(&new_vectorlETLArHitgR);
      instance.SetNewArray(&newArray_vectorlETLArHitgR);
      instance.SetDelete(&delete_vectorlETLArHitgR);
      instance.SetDeleteArray(&deleteArray_vectorlETLArHitgR);
      instance.SetDestructor(&destruct_vectorlETLArHitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TLArHit> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TLArHit>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETLArHitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TLArHit>*)0x0)->GetClass();
      vectorlETLArHitgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETLArHitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETLArHitgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TLArHit> : new vector<TLArHit>;
   }
   static void *newArray_vectorlETLArHitgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TLArHit>[nElements] : new vector<TLArHit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETLArHitgR(void *p) {
      delete ((vector<TLArHit>*)p);
   }
   static void deleteArray_vectorlETLArHitgR(void *p) {
      delete [] ((vector<TLArHit>*)p);
   }
   static void destruct_vectorlETLArHitgR(void *p) {
      typedef vector<TLArHit> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TLArHit>

namespace {
  void TriggerDictionaryInitialization_TLArEvent_Dict_Impl() {
    static const char* headers[] = {
"TLArEvent.hxx",
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
#line 1 "TLArEvent_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TLArHit.hxx")))  __attribute__((annotate("$clingAutoload$TLArEvent.hxx")))  TLArHit;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$TLArEvent.hxx")))  TLArEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TLArEvent_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TLArEvent.hxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TLArEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TLArEvent_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TLArEvent_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TLArEvent_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TLArEvent_Dict() {
  TriggerDictionaryInitialization_TLArEvent_Dict_Impl();
}
