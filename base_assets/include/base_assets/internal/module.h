#if !defined(BASE_ASSETS_API)
	#define BASE_ASSETS_API /* NOTHING */

	#if defined(WIN32) || defined(WIN64)
		#undef BASE_ASSETS_API
		#if defined(base_assets_EXPORTS)
			#define BASE_ASSETS_API __declspec(dllexport)
		#else
			#define BASE_ASSETS_API __declspec(dllimport)
		#endif
	#endif // defined(WIN32) || defined(WIN64)

#endif // !defined(BASE_ASSETS_API)

