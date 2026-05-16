#if !defined(ACSU_API)
	#define ACSU_API /* NOTHING */

	#if defined(WIN32) || defined(WIN64)
		#undef ACSU_API
		#if defined(acsu_EXPORTS)
			#define ACSU_API __declspec(dllexport)
		#else
			#define ACSU_API __declspec(dllimport)
		#endif
	#endif // defined(WIN32) || defined(WIN64)

#endif // !defined(ACSU_API)

