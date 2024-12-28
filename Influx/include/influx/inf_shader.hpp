#if !defined(INF_SHADER_HPP)
#define INF_SHADER_HPP

#include "inf_loader.hpp"

namespace inf {
	namespace shader {
		using handle_t = uint64_t;
		inline handle_t Create(const std::filesystem::path& filename, shader::stage_t stage)
		{
			return Loader::create_shader(filename, stage);
		}
		inline void Destroy(handle_t shader)
		{
			return Loader::destroy_shader(shader);
		}

		class shader_t {
		public:
			inline shader_t(const std::filesystem::path& filename, shader::stage_t stage)
			: handle(Loader::create_shader(filename, stage))
			{}
			inline void destroy(void) { Loader::destroy_shader(handle); handle = NEO_INVALID_HANDLE; }
			inline ~shader_t(void) { this->destroy(); }

			inline operator bool(void) const { return handle != NEO_INVALID_HANDLE; }
		public:
			handle_t handle;
		};
	} // namepsace shader
	using shader_t = shader::shader_t;
} // namespace inf

#endif // INF_SHADER_HPP