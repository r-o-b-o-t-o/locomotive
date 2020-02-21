#ifndef LOCOMOTIVE_ARENA_H
#define LOCOMOTIVE_ARENA_H

#include "locomotive/locomotive.h"

#include <new>
#include <cstdint>

namespace Locomotive {
	class Arena {
	public:
		Arena() :
				memory(nullptr),
				cursor(0),
				size(0) {
		}
		Arena(Arena &other) = delete;

		~Arena() {
			this->Destroy();
		}

		Arena &operator=(Arena &rhs) = delete;

		void Initialise(uint32_t size) {
			if (memory != nullptr) {
				return;
			}
			this->cursor = 0;
			this->size = size;
			this->memory = new uint8_t[size];
		}

		void Destroy() {
			if (this->memory != nullptr) {
				delete[] this->memory;
				this->memory = nullptr;
			}
		}

		void Reset() {
			this->cursor = 0;
		}

		template <typename T>
		T* Allocate() {
			if (this->cursor >= this->size) {
				return nullptr;
			}

			T* data = (T*)&this->memory[this->cursor];
			this->cursor += sizeof(T);

			::operator new(sizeof(T), data);

			return data;
		}

		template <typename T>
		void Deallocate(T* ptr) {
			if (ptr == nullptr) {
				return;
			}
			ptr->~T();
		}

	private:
		uint8_t* memory;
		uint32_t cursor;
		uint32_t size;
	};
}

#endif
