#if !defined(NEO_UTILS_HPP)
#define NEO_UTILS_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
	using byte_t = char;
	using ubyte_t = unsigned char;

	enum class type_t : uint8_t {
		None = 0,
		Byte, UByte,
		Char = Byte, UChar = UByte,
		Int8 = Byte, UInt8 = UByte,
		Int16, UInt16,
		Int32, UInt32,
		Int64, UInt64,
		Float,
		Double
	};

	inline uint32_t SizeOf(type_t type)
	{
		switch (type)
		{
		case type_t::Int8:   return 1u;
		case type_t::UInt8:  return 1u;
		case type_t::Int16:  return 2u;
		case type_t::UInt16: return 2u;
		case type_t::Int32:  return 4u;
		case type_t::UInt32: return 4u;
		case type_t::Int64:  return 8u;
		case type_t::UInt64: return 8u;
		case type_t::Float:  return 4u;
		case type_t::Double: return 8u;
		}
		return 0u;
	}

	template<typename T>
	[[nodiscard]] inline T* tmalloc(size_t count)
	{
		return (T*)malloc(count * sizeof(T));
	}

	template<typename T>
	[[nodiscard]] inline T* tcalloc(size_t count)
	{
		return (T*)calloc(count, sizeof(T));
	}

	template<typename T>
	[[nodiscard]] inline T* trealloc(T* buffer, size_t count)
	{
		return (T*)realloc(buffer, count * sizeof(T));
	}

	[[nodiscard]] inline int32_t Round32(float num)  { return (int32_t)floor(num + 0.5f); }
	[[nodiscard]] inline int64_t Round64(double num) { return (int64_t)floor(num + 0.5); }

	[[nodiscard]] inline bool LittleEndian(void)
	{
		uint32_t n = 1;
		return *(char*)&n == 1;
	}

	// returns a malloc allocated buffer
	[[nodiscard]] inline uint16_t* BytesToInt16(byte_t* bytes, size_t size, bool data_big_endian = true)
	{
		if (size % 2)
			return nullptr;

		uint16_t* bytes16 = tmalloc<uint16_t>(size / 2);
		if (data_big_endian)
			for (size_t i = 0; i < size; i += 2)
				bytes16[i / 2] = bytes[i + 1] | (uint16_t)bytes[i] << 8;
		else
			for (size_t i = 0; i < size; i += 2)
				bytes16[i / 2] = bytes[i] | (uint16_t)bytes[i + 1] << 8;

		return bytes16;
	}

	// returns a malloc allocated buffer
	[[nodiscard]] inline uint32_t* BytesToInt32(byte_t* bytes, size_t size, bool data_big_endian = true)
	{
		if (size % 4)
			return nullptr;

		uint32_t* bytes32 = tmalloc<uint32_t>(size / 4);
		if (data_big_endian)
			for (size_t i = 0; i < size; i += 4)
				bytes32[i / 4] = bytes[i + 3]  | (uint32_t)bytes[i + 2] << 8
				| (uint32_t)bytes[i + 1] << 16 | (uint32_t)bytes[i] << 24;
		else
			for (size_t i = 0; i < size; i += 4)
				bytes32[i / 4] = bytes[i] | (uint32_t)bytes[i + 1] << 8
				| (uint32_t)bytes[i + 2] << 16 | (uint32_t)bytes[i + 3] << 24;

		return bytes32;
	}

	// returns a malloc allocated buffer
	[[nodiscard]] inline uint64_t* BytesToInt64(byte_t* bytes, size_t size, bool data_big_endian = true)
	{
		if (size % 8)
			return nullptr;

		uint64_t* bytes32 = tmalloc<uint64_t>(size / 8);
		if (data_big_endian)
			for (size_t i = 0; i < size; i += 8)
				bytes32[i / 4] = bytes[i + 7]  | (uint64_t)bytes[i + 6] << 8
				| (uint64_t)bytes[i + 5] << 16 | (uint64_t)bytes[i + 4] << 24
				| (uint64_t)bytes[i + 3] << 32 | (uint64_t)bytes[i + 2] << 40
				| (uint64_t)bytes[i + 1] << 48 | (uint64_t)bytes[i] << 56;
		else
			for (size_t i = 0; i < size; i += 8)
				bytes32[i / 4] = bytes[i] | (uint64_t)bytes[i + 1] << 8
				| (uint64_t)bytes[i + 2] << 16 | (uint64_t)bytes[i + 3] << 24
				| (uint64_t)bytes[i + 4] << 32 | (uint64_t)bytes[i + 5] << 40
				| (uint64_t)bytes[i + 6] << 48 | (uint64_t)bytes[i + 7] << 56;

		return bytes32;
	}
}

#endif // NEO_UTILS_HPP