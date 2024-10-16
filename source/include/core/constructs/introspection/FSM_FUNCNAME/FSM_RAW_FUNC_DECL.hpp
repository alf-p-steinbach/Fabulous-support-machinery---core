#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// Can't test directly for existence of the pseudo-macros, so must test compiler ids:
#if     defined( _MSC_VER )      // Visual C++
#   define FSM_RAW_FUNC_DECL                                __FUNCSIG__
#elif   defined( __GNUC__ ) or defined( __clang__ )
#   define FSM_RAW_FUNC_DECL                                __PRETTY_FUNCTION__
#else
#   define FSM_RAW_FUNC_DECL                                __func__
#endif
