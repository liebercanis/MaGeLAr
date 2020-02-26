// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TGeEvent_Dict

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
#include "TGeEvent.hxx"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TGeEvent(void *p = 0);
   static void *newArray_TGeEvent(Long_t size, void *p);
   static void delete_TGeEvent(void *p);
   static void deleteArray_TGeEvent(void *p);
   static void destruct_TGeEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TGeEvent*)
   {
      ::TGeEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TGeEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TGeEvent", ::TGeEvent::Class_Version(), "TGeEvent.hxx", 16,
                  typeid(::TGeEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TGeEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TGeEvent) );
      instance.SetNew(&new_TGeEvent);
      instance.SetNewArray(&newArray_TGeEvent);
      instance.SetDelete(&delete_TGeEvent);
      instance.SetDeleteArray(&deleteArray_TGeEvent);
      instance.SetDestructor(&destruct_TGeEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TGeEvent*)
   {
      return GenerateInitInstanceLocal((::TGeEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TGeEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TGeEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TGeEvent::Class_Name()
{
   return "TGeEvent";
}

//______________________________________________________________________________
const char *TGeEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGeEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TGeEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGeEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TGeEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGeEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TGeEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGeEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TGeEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TGeEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TGeEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TGeEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TGeEvent(void *p) {
      return  p ? new(p) ::TGeEvent : new ::TGeEvent;
   }
   static void *newArray_TGeEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TGeEvent[nElements] : new ::TGeEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TGeEvent(void *p) {
      delete ((::TGeEvent*)p);
   }
   static void deleteArray_TGeEvent(void *p) {
      delete [] ((::TGeEvent*)p);
   }
   static void destruct_TGeEvent(void *p) {
      typedef ::TGeEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TGeEvent

namespace ROOT {
   static TClass *vectorlETGeDetgR_Dictionary();
   static void vectorlETGeDetgR_TClassManip(TClass*);
   static void *new_vectorlETGeDetgR(void *p = 0);
   static void *newArray_vectorlETGeDetgR(Long_t size, void *p);
   static void delete_vectorlETGeDetgR(void *p);
   static void deleteArray_vectorlETGeDetgR(void *p);
   static void destruct_vectorlETGeDetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGeDet>*)
   {
      vector<TGeDet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGeDet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGeDet>", -2, "vector", 210,
                  typeid(vector<TGeDet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGeDetgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TGeDet>) );
      instance.SetNew(&new_vectorlETGeDetgR);
      instance.SetNewArray(&newArray_vectorlETGeDetgR);
      instance.SetDelete(&delete_vectorlETGeDetgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGeDetgR);
      instance.SetDestructor(&destruct_vectorlETGeDetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGeDet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TGeDet>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGeDetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TGeDet>*)0x0)->GetClass();
      vectorlETGeDetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGeDetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGeDetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGeDet> : new vector<TGeDet>;
   }
   static void *newArray_vectorlETGeDetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGeDet>[nElements] : new vector<TGeDet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGeDetgR(void *p) {
      delete ((vector<TGeDet>*)p);
   }
   static void deleteArray_vectorlETGeDetgR(void *p) {
      delete [] ((vector<TGeDet>*)p);
   }
   static void destruct_vectorlETGeDetgR(void *p) {
      typedef vector<TGeDet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TGeDet>

namespace {
  void TriggerDictionaryInitialization_TGeEvent_Dict_Impl() {
    static const char* headers[] = {
"TGeEvent.hxx",
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
#line 1 "TGeEvent_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TGeDet.hxx")))  __attribute__((annotate("$clingAutoload$TGeEvent.hxx")))  TGeDet;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$TGeEvent.hxx")))  TGeEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TGeEvent_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TGeEvent.hxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TGeEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TGeEvent_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TGeEvent_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TGeEvent_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TGeEvent_Dict() {
  TriggerDictionaryInitialization_TGeEvent_Dict_Impl();
}
