#if !defined(NEO_FRAME_BUFFER_HPP)
#define NEO_FRAME_BUFFER_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
	class FrameBuffer {
	public:
		FrameBuffer(void);
		~FrameBuffer(void);
		static FrameBuffer* Get(void) { return FrameBuffer::m_This; }
	public:
		void initialize(size_t size);
		void reallocate(size_t new_size);
		void flush(void);

		void* add(size_t size);
		template<typename T> inline T* add() { return (T*)(this->add(sizeof(T))); }
		template<typename T> inline size_t push(const T& value) {
			*((T*)(this->add(sizeof(T)))) = value;
			return m_InsertIndex - sizeof(T);
		}
		// returns a pointer to the pushed memory instead of an index
		template<typename T> inline T* push_p(const T& value) {
			*((T*)(this->add(sizeof(T)))) = value;
			return (T*)(m_Buffer + (m_InsertIndex - sizeof(T)));
		}

		void* at(size_t index);
		template<typename T> inline T* at(size_t index) { return (T*)(this->at(index)); }
		template<typename T> inline void set_at(const T& value, size_t index) { *((T*)this->at(index)) = value; }

		inline void* buffer(void) { return (void*)m_Buffer; }
		inline size_t size(void) const { return m_Size; }
		inline size_t insert_index(void) const { return m_InsertIndex; }
	private:
		byte_t* m_Buffer;
		size_t m_Size, m_InsertIndex;

		static FrameBuffer* m_This;
	};
}

#endif // NEO_FRAME_BUFFER_HPP