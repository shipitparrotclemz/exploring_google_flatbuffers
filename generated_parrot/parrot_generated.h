// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PARROT_PARROTSCHEMA_H_
#define FLATBUFFERS_GENERATED_PARROT_PARROTSCHEMA_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 3 &&
              FLATBUFFERS_VERSION_REVISION == 3,
             "Non-compatible flatbuffers version included");

namespace ParrotSchema {

struct Position;
struct PositionBuilder;

struct Talent;
struct TalentBuilder;

struct Parrot;
struct ParrotBuilder;

enum Color : int8_t {
  Color_Red = 0,
  Color_Green = 1,
  Color_Blue = 2,
  Color_MIN = Color_Red,
  Color_MAX = Color_Blue
};

inline const Color (&EnumValuesColor())[3] {
  static const Color values[] = {
    Color_Red,
    Color_Green,
    Color_Blue
  };
  return values;
}

inline const char * const *EnumNamesColor() {
  static const char * const names[4] = {
    "Red",
    "Green",
    "Blue",
    nullptr
  };
  return names;
}

inline const char *EnumNameColor(Color e) {
  if (::flatbuffers::IsOutRange(e, Color_Red, Color_Blue)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesColor()[index];
}

enum Level : int8_t {
  Level_One = 0,
  Level_Two = 1,
  Level_Three = 2,
  Level_Four = 3,
  Level_Five = 4,
  Level_MIN = Level_One,
  Level_MAX = Level_Five
};

inline const Level (&EnumValuesLevel())[5] {
  static const Level values[] = {
    Level_One,
    Level_Two,
    Level_Three,
    Level_Four,
    Level_Five
  };
  return values;
}

inline const char * const *EnumNamesLevel() {
  static const char * const names[6] = {
    "One",
    "Two",
    "Three",
    "Four",
    "Five",
    nullptr
  };
  return names;
}

inline const char *EnumNameLevel(Level e) {
  if (::flatbuffers::IsOutRange(e, Level_One, Level_Five)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesLevel()[index];
}

struct Position FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef PositionBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_X = 4,
    VT_Y = 6,
    VT_Z = 8
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  float z() const {
    return GetField<float>(VT_Z, 0.0f);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X, 4) &&
           VerifyField<float>(verifier, VT_Y, 4) &&
           VerifyField<float>(verifier, VT_Z, 4) &&
           verifier.EndTable();
  }
};

struct PositionBuilder {
  typedef Position Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(Position::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(Position::VT_Y, y, 0.0f);
  }
  void add_z(float z) {
    fbb_.AddElement<float>(Position::VT_Z, z, 0.0f);
  }
  explicit PositionBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Position> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Position>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Position> CreatePosition(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f,
    float z = 0.0f) {
  PositionBuilder builder_(_fbb);
  builder_.add_z(z);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct Talent FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef TalentBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_LEVEL = 6
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  ParrotSchema::Level level() const {
    return static_cast<ParrotSchema::Level>(GetField<int8_t>(VT_LEVEL, 0));
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int8_t>(verifier, VT_LEVEL, 1) &&
           verifier.EndTable();
  }
};

struct TalentBuilder {
  typedef Talent Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Talent::VT_NAME, name);
  }
  void add_level(ParrotSchema::Level level) {
    fbb_.AddElement<int8_t>(Talent::VT_LEVEL, static_cast<int8_t>(level), 0);
  }
  explicit TalentBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Talent> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Talent>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Talent> CreateTalent(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ParrotSchema::Level level = ParrotSchema::Level_One) {
  TalentBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_level(level);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Talent> CreateTalentDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    ParrotSchema::Level level = ParrotSchema::Level_One) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return ParrotSchema::CreateTalent(
      _fbb,
      name__,
      level);
}

struct Parrot FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef ParrotBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POSITION = 4,
    VT_NAME = 6,
    VT_COLOR = 8,
    VT_TALENTS = 10
  };
  const ParrotSchema::Position *position() const {
    return GetPointer<const ParrotSchema::Position *>(VT_POSITION);
  }
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  ParrotSchema::Color color() const {
    return static_cast<ParrotSchema::Color>(GetField<int8_t>(VT_COLOR, 0));
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<ParrotSchema::Talent>> *talents() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<ParrotSchema::Talent>> *>(VT_TALENTS);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_POSITION) &&
           verifier.VerifyTable(position()) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int8_t>(verifier, VT_COLOR, 1) &&
           VerifyOffset(verifier, VT_TALENTS) &&
           verifier.VerifyVector(talents()) &&
           verifier.VerifyVectorOfTables(talents()) &&
           verifier.EndTable();
  }
};

struct ParrotBuilder {
  typedef Parrot Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_position(::flatbuffers::Offset<ParrotSchema::Position> position) {
    fbb_.AddOffset(Parrot::VT_POSITION, position);
  }
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Parrot::VT_NAME, name);
  }
  void add_color(ParrotSchema::Color color) {
    fbb_.AddElement<int8_t>(Parrot::VT_COLOR, static_cast<int8_t>(color), 0);
  }
  void add_talents(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ParrotSchema::Talent>>> talents) {
    fbb_.AddOffset(Parrot::VT_TALENTS, talents);
  }
  explicit ParrotBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Parrot> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Parrot>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Parrot> CreateParrot(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<ParrotSchema::Position> position = 0,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ParrotSchema::Color color = ParrotSchema::Color_Red,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<ParrotSchema::Talent>>> talents = 0) {
  ParrotBuilder builder_(_fbb);
  builder_.add_talents(talents);
  builder_.add_name(name);
  builder_.add_position(position);
  builder_.add_color(color);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Parrot> CreateParrotDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<ParrotSchema::Position> position = 0,
    const char *name = nullptr,
    ParrotSchema::Color color = ParrotSchema::Color_Red,
    const std::vector<::flatbuffers::Offset<ParrotSchema::Talent>> *talents = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto talents__ = talents ? _fbb.CreateVector<::flatbuffers::Offset<ParrotSchema::Talent>>(*talents) : 0;
  return ParrotSchema::CreateParrot(
      _fbb,
      position,
      name__,
      color,
      talents__);
}

inline const ParrotSchema::Parrot *GetParrot(const void *buf) {
  return ::flatbuffers::GetRoot<ParrotSchema::Parrot>(buf);
}

inline const ParrotSchema::Parrot *GetSizePrefixedParrot(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<ParrotSchema::Parrot>(buf);
}

inline bool VerifyParrotBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<ParrotSchema::Parrot>(nullptr);
}

inline bool VerifySizePrefixedParrotBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<ParrotSchema::Parrot>(nullptr);
}

inline void FinishParrotBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<ParrotSchema::Parrot> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedParrotBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<ParrotSchema::Parrot> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace ParrotSchema

#endif  // FLATBUFFERS_GENERATED_PARROT_PARROTSCHEMA_H_
