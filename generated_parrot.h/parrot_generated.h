// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PARROT_PARROT_H_
#define FLATBUFFERS_GENERATED_PARROT_PARROT_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 3 &&
              FLATBUFFERS_VERSION_REVISION == 3,
             "Non-compatible flatbuffers version included");

namespace Parrot {

struct Position;

struct Talent;
struct TalentBuilder;

struct Parrot;
struct ParrotBuilder;

enum class Color : int8_t {
  Red = 0,
  Green = 1,
  Blue = 2,
  MIN = Red,
  MAX = Blue
};

inline const Color (&EnumValuesColor())[3] {
  static const Color values[] = {
    Color::Red,
    Color::Green,
    Color::Blue
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
  if (::flatbuffers::IsOutRange(e, Color::Red, Color::Blue)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesColor()[index];
}

enum class Level : int8_t {
  One = 0,
  Two = 1,
  Three = 2,
  Four = 3,
  Five = 4,
  MIN = One,
  MAX = Five
};

inline const Level (&EnumValuesLevel())[5] {
  static const Level values[] = {
    Level::One,
    Level::Two,
    Level::Three,
    Level::Four,
    Level::Five
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
  if (::flatbuffers::IsOutRange(e, Level::One, Level::Five)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesLevel()[index];
}

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Position FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;

 public:
  struct Traits;
  Position()
      : x_(0),
        y_(0),
        z_(0) {
  }
  Position(float _x, float _y, float _z)
      : x_(::flatbuffers::EndianScalar(_x)),
        y_(::flatbuffers::EndianScalar(_y)),
        z_(::flatbuffers::EndianScalar(_z)) {
  }
  float x() const {
    return ::flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return ::flatbuffers::EndianScalar(y_);
  }
  float z() const {
    return ::flatbuffers::EndianScalar(z_);
  }
};
FLATBUFFERS_STRUCT_END(Position, 12);

struct Position::Traits {
  using type = Position;
};

struct Talent FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef TalentBuilder Builder;
  struct Traits;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_LEVEL = 6
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  Parrot::Level level() const {
    return static_cast<Parrot::Level>(GetField<int8_t>(VT_LEVEL, 0));
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
  void add_level(Parrot::Level level) {
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
    Parrot::Level level = Parrot::Level::One) {
  TalentBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_level(level);
  return builder_.Finish();
}

struct Talent::Traits {
  using type = Talent;
  static auto constexpr Create = CreateTalent;
};

inline ::flatbuffers::Offset<Talent> CreateTalentDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    Parrot::Level level = Parrot::Level::One) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return Parrot::CreateTalent(
      _fbb,
      name__,
      level);
}

struct Parrot FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef ParrotBuilder Builder;
  struct Traits;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POSITION = 4,
    VT_NAME = 6,
    VT_COLOR = 8,
    VT_TALENTS = 10
  };
  const Parrot::Position *position() const {
    return GetStruct<const Parrot::Position *>(VT_POSITION);
  }
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  Parrot::Color color() const {
    return static_cast<Parrot::Color>(GetField<int8_t>(VT_COLOR, 0));
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<Parrot::Talent>> *talents() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Parrot::Talent>> *>(VT_TALENTS);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<Parrot::Position>(verifier, VT_POSITION, 4) &&
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
  void add_position(const Parrot::Position *position) {
    fbb_.AddStruct(Parrot::VT_POSITION, position);
  }
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Parrot::VT_NAME, name);
  }
  void add_color(Parrot::Color color) {
    fbb_.AddElement<int8_t>(Parrot::VT_COLOR, static_cast<int8_t>(color), 0);
  }
  void add_talents(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Parrot::Talent>>> talents) {
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
    const Parrot::Position *position = nullptr,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    Parrot::Color color = Parrot::Color::Red,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Parrot::Talent>>> talents = 0) {
  ParrotBuilder builder_(_fbb);
  builder_.add_talents(talents);
  builder_.add_name(name);
  builder_.add_position(position);
  builder_.add_color(color);
  return builder_.Finish();
}

struct Parrot::Traits {
  using type = Parrot;
  static auto constexpr Create = CreateParrot;
};

inline ::flatbuffers::Offset<Parrot> CreateParrotDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const Parrot::Position *position = nullptr,
    const char *name = nullptr,
    Parrot::Color color = Parrot::Color::Red,
    const std::vector<::flatbuffers::Offset<Parrot::Talent>> *talents = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto talents__ = talents ? _fbb.CreateVector<::flatbuffers::Offset<Parrot::Talent>>(*talents) : 0;
  return Parrot::CreateParrot(
      _fbb,
      position,
      name__,
      color,
      talents__);
}

inline const Parrot::Parrot *GetParrot(const void *buf) {
  return ::flatbuffers::GetRoot<Parrot::Parrot>(buf);
}

inline const Parrot::Parrot *GetSizePrefixedParrot(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<Parrot::Parrot>(buf);
}

inline bool VerifyParrotBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Parrot::Parrot>(nullptr);
}

inline bool VerifySizePrefixedParrotBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Parrot::Parrot>(nullptr);
}

inline void FinishParrotBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<Parrot::Parrot> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedParrotBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<Parrot::Parrot> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace Parrot

#endif  // FLATBUFFERS_GENERATED_PARROT_PARROT_H_