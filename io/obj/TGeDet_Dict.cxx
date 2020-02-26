// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TGeDet_Dict

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
#include "TGeDet.hxx"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TGeDet(void *p = 0);
   static void *newArray_TGeDet(Long_t size, void *p);
   static void delete_TGeDet(void *p);
   static void deleteArray_TGeDet(void *p);
   static void destruct_TGeDet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TGeDet*)
   {
      ::TGeDet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TGeDet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TGeDet", ::TGeDet::Class_Version(), "TGeDet.hxx", 14,
                  typeid(::TGeDet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TGeDet::Dictionary, isa_proxy, 4,
                  sizeof(::TGeDet) );
      instance.SetNew(&new_TGeDet);
      instance.SetNewArray(&newArray_TGeDet);
      instance.SetDelete(&delete_TGeDet);
      instance.SetDeleteArray(&deleteArray_TGeDet);
      instance.SetDestructor(&destruct_TGeDet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TGeDet*)
   {
      return GenerateInitInstanceLocal((::TGeDet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TGeDet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TGeDet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TGeDet::Class_Name()
{
   return "TGeDet";
}

//______________________________________________________________________________
const char *TGeDet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGeDet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TGeDet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TGeDet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TGeDet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGeDet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TGeDet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TGeDet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TGeDet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TGeDet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TGeDet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TGeDet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TGeDet(void *p) {
      return  p ? new(p) ::TGeDet : new ::TGeDet;
   }
   static void *newArray_TGeDet(Long_t nElements, void *p) {
      return p ? new(p) ::TGeDet[nElements] : new ::TGeDet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TGeDet(void *p) {
      delete ((::TGeDet*)p);
   }
   static void deleteArray_TGeDet(void *p) {
      delete [] ((::TGeDet*)p);
   }
   static void destruct_TGeDet(void *p) {
      typedef ::TGeDet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TGeDet

namespace ROOT {
   static TClass *maplEdoublecOTGeHitgR_Dictionary();
   static void maplEdoublecOTGeHitgR_TClassManip(TClass*);
   static void *new_maplEdoublecOTGeHitgR(void *p = 0);
   static void *newArray_maplEdoublecOTGeHitgR(Long_t size, void *p);
   static void delete_maplEdoublecOTGeHitgR(void *p);
   static void deleteArray_maplEdoublecOTGeHitgR(void *p);
   static void destruct_maplEdoublecOTGeHitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<double,TGeHit>*)
   {
      map<double,TGeHit> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<double,TGeHit>));
      static ::ROOT::TGenericClassInfo 
         instance("map<double,TGeHit>", -2, "map", 96,
                  typeid(map<double,TGeHit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEdoublecOTGeHitgR_Dictionary, isa_proxy, 4,
                  sizeof(map<double,TGeHit>) );
      instance.SetNew(&new_maplEdoublecOTGeHitgR);
      instance.SetNewArray(&newArray_maplEdoublecOTGeHitgR);
      instance.SetDelete(&delete_maplEdoublecOTGeHitgR);
      instance.SetDeleteArray(&deleteArray_maplEdoublecOTGeHitgR);
      instance.SetDestructor(&destruct_maplEdoublecOTGeHitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<double,TGeHit> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<double,TGeHit>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEdoublecOTGeHitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<double,TGeHit>*)0x0)->GetClass();
      maplEdoublecOTGeHitgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEdoublecOTGeHitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEdoublecOTGeHitgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<double,TGeHit> : new map<double,TGeHit>;
   }
   static void *newArray_maplEdoublecOTGeHitgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<double,TGeHit>[nElements] : new map<double,TGeHit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEdoublecOTGeHitgR(void *p) {
      delete ((map<double,TGeHit>*)p);
   }
   static void deleteArray_maplEdoublecOTGeHitgR(void *p) {
      delete [] ((map<double,TGeHit>*)p);
   }
   static void destruct_maplEdoublecOTGeHitgR(void *p) {
      typedef map<double,TGeHit> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<double,TGeHit>

namespace {
  void TriggerDictionaryInitialization_TGeDet_Dict_Impl() {
    static const char* headers[] = {
"TGeDet.hxx",
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
#line 1 "TGeDet_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TGeHit.hxx")))  __attribute__((annotate("$clingAutoload$TGeDet.hxx")))  TGeHit;
namespace std{template <typename _Tp> struct __attribute__((annotate("$clingAutoload$bits/stl_function.h")))  __attribute__((annotate("$clingAutoload$string")))  less;
}
namespace std{template <class _T1, class _T2> struct __attribute__((annotate("$clingAutoload$bits/stl_pair.h")))  __attribute__((annotate("$clingAutoload$string")))  pair;
}
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$TGeDet.hxx")))  TGeDet;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TGeDet_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TGeDet.hxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TGeDet", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TGeDet_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TGeDet_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TGeDet_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TGeDet_Dict() {
  TriggerDictionaryInitialization_TGeDet_Dict_Impl();
}
