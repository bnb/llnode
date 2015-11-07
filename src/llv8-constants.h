#ifndef SRC_LLV8_CONSTANTS_H_
#define SRC_LLV8_CONSTANTS_H_

#include <lldb/API/LLDB.h>

namespace llnode {
namespace v8 {
namespace constants {

class Module {
 public:
  Module() : loaded_(false) {
  }

  inline bool is_loaded() const { return loaded_; }

  void SetTarget(lldb::SBTarget);

 protected:
  int64_t LoadConstant(const char* name, int64_t def = -1);
  int64_t LoadConstant(const char* name, const char* fallback,
      int64_t def = -1);

  lldb::SBTarget target_;
  bool loaded_;
};

#define MODULE_DEFAULT_METHODS(NAME)                                          \
    NAME() {}                                                                 \
    inline NAME* operator()() {                                               \
      if (loaded_) return this;                                               \
      loaded_ = true;                                                         \
      Load();                                                                 \
      return this;                                                            \
    }

class Common : public Module {
 public:
  MODULE_DEFAULT_METHODS(Common);

  int64_t kPointerSize;

 protected:
  void Load();
};

class Smi : public Module {
 public:
  MODULE_DEFAULT_METHODS(Smi);

  int64_t kTag;
  int64_t kTagMask;
  int64_t kShiftSize;

 protected:
  void Load();
};

class HeapObject : public Module {
 public:
  MODULE_DEFAULT_METHODS(HeapObject);

  int64_t kTag;
  int64_t kTagMask;

  int64_t kMapOffset;

 protected:
  void Load();
};

class Map : public Module {
 public:
  MODULE_DEFAULT_METHODS(Map);

  int64_t kInstanceAttrsOffset;
  int64_t kMaybeConstructorOffset;
  int64_t kInstanceDescriptorsOffset;
  int64_t kBitField3Offset;
  int64_t kInObjectPropertiesOffset;
  int64_t kInstanceSizeOffset;

  int64_t kDictionaryMapShift;

 protected:
  void Load();
};

class JSObject : public Module {
 public:
  MODULE_DEFAULT_METHODS(JSObject);

  int64_t kPropertiesOffset;
  int64_t kElementsOffset;

 protected:
  void Load();
};

class JSArray : public Module {
 public:
  MODULE_DEFAULT_METHODS(JSArray);

  int64_t kLengthOffset;

 protected:
  void Load();
};

class JSFunction : public Module {
 public:
  MODULE_DEFAULT_METHODS(JSFunction);

  int64_t kSharedInfoOffset;

 protected:
  void Load();
};

class SharedInfo : public Module {
 public:
  MODULE_DEFAULT_METHODS(SharedInfo);

  int64_t kNameOffset;
  int64_t kInferredNameOffset;
  int64_t kScriptOffset;
  int64_t kStartPositionOffset;
  int64_t kParameterCountOffset;

  int64_t kStartPositionShift;

 protected:
  void Load();
};

class Script : public Module {
 public:
  MODULE_DEFAULT_METHODS(Script);

  int64_t kNameOffset;
  int64_t kLineOffsetOffset;
  int64_t kSourceOffset;
  int64_t kLineEndsOffset;

 protected:
  void Load();
};

class String : public Module {
 public:
  MODULE_DEFAULT_METHODS(String);

  int64_t kEncodingMask;
  int64_t kRepresentationMask;

  // Encoding
  int64_t kOneByteStringTag;
  int64_t kTwoByteStringTag;

  // Representation
  int64_t kSeqStringTag;
  int64_t kConsStringTag;
  int64_t kSlicedStringTag;
  int64_t kExternalStringTag;

  int64_t kLengthOffset;

 protected:
  void Load();
};

class OneByteString : public Module {
 public:
  MODULE_DEFAULT_METHODS(OneByteString);

  int64_t kCharsOffset;

 protected:
  void Load();
};

class TwoByteString : public Module {
 public:
  MODULE_DEFAULT_METHODS(TwoByteString);

  int64_t kCharsOffset;

 protected:
  void Load();
};

class ConsString : public Module {
 public:
  MODULE_DEFAULT_METHODS(ConsString);

  int64_t kFirstOffset;
  int64_t kSecondOffset;

 protected:
  void Load();
};

class SlicedString : public Module {
 public:
  MODULE_DEFAULT_METHODS(SlicedString);

  int64_t kParentOffset;
  int64_t kOffsetOffset;

 protected:
  void Load();
};

class FixedArrayBase : public Module {
 public:
  MODULE_DEFAULT_METHODS(FixedArrayBase);

  int64_t kLengthOffset;

 protected:
  void Load();
};

class FixedArray : public Module {
 public:
  MODULE_DEFAULT_METHODS(FixedArray);

  int64_t kDataOffset;

 protected:
  void Load();
};

class Oddball : public Module {
 public:
  MODULE_DEFAULT_METHODS(Oddball);

  int64_t kKindOffset;

  int64_t kException;
  int64_t kFalse;
  int64_t kTrue;
  int64_t kUndefined;
  int64_t kNull;
  int64_t kTheHole;
  int64_t kUninitialized;

 protected:
  void Load();
};

class JSArrayBuffer : public Module {
 public:
  MODULE_DEFAULT_METHODS(JSArrayBuffer);

  int64_t kKindOffset;

  int64_t kBackingStoreOffset;
  int64_t kByteLengthOffset;
  int64_t kBitFieldOffset;

  int64_t kWasNeuteredMask;

 protected:
  void Load();
};

class JSArrayBufferView : public Module {
 public:
  MODULE_DEFAULT_METHODS(JSArrayBufferView);

  int64_t kBufferOffset;
  int64_t kByteOffsetOffset;
  int64_t kByteLengthOffset;

 protected:
  void Load();
};

class DescriptorArray : public Module {
 public:
  MODULE_DEFAULT_METHODS(DescriptorArray);

  int64_t kDetailsOffset;
  int64_t kKeyOffset;
  int64_t kValueOffset;

  int64_t kPropertyIndexMask;
  int64_t kPropertyIndexShift;
  int64_t kPropertyTypeMask;
  int64_t kFieldType;

  int64_t kFirstIndex;
  int64_t kSize;

 protected:
  void Load();
};

class NameDictionary : public Module {
 public:
  MODULE_DEFAULT_METHODS(NameDictionary);

  int64_t kKeyOffset;
  int64_t kValueOffset;

  int64_t kEntrySize;
  int64_t kPrefixSize;

 protected:
  void Load();
};

class Frame : public Module {
 public:
  MODULE_DEFAULT_METHODS(Frame);

  int64_t kContextOffset;
  int64_t kFunctionOffset;
  int64_t kArgsOffset;
  int64_t kMarkerOffset;

  int64_t kAdaptorFrame;
  int64_t kEntryFrame;
  int64_t kEntryConstructFrame;
  int64_t kExitFrame;
  int64_t kInternalFrame;
  int64_t kConstructFrame;
  int64_t kJSFrame;
  int64_t kOptimizedFrame;

 protected:
  void Load();
};

class Types : public Module {
 public:
  MODULE_DEFAULT_METHODS(Types);

  int64_t kFirstNonstringType;

  int64_t kMapType;
  int64_t kGlobalObjectType;
  int64_t kOddballType;
  int64_t kJSObjectType;
  int64_t kJSArrayType;
  int64_t kCodeType;
  int64_t kJSFunctionType;
  int64_t kFixedArrayType;
  int64_t kJSArrayBufferType;
  int64_t kJSTypedArrayType;

 protected:
  void Load();
};

#undef MODULE_DEFAULT_METHODS

}  // namespace constants
}  // namespace v8
}  // namespace llnode

#endif  // SRC_LLV8_CONSTANTS_H_