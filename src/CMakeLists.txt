# Make sure the user is not executing this script directly
if(NOT InMV)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InMV)

if (BuildMVMP OR BuildMVDED)
	# Libraries
	if(WIN32)
		set(MVMPDEDLibraries ${MVMPDEDLibraries} "winmm" "ws2_32")
	else()
		find_package(Threads)
		set(MVMPDEDLibraries ${MVMPDEDLibraries} ${CMAKE_THREAD_LIBS_INIT})
		set(MVMPDEDLibraries ${MVMPDEDLibraries} ${CMAKE_DL_LIBS})

		# ouned: FIXME SDL2 is currently required even for building only the jk2mvded
		# only the headers though
		find_package(SDL2)
		if(NOT SDL2_FOUND)
			message(FATAL_ERROR "libsdl2 dev files not found!")
		endif()
		set(MVMPDEDIncludeDirs ${MVMPDEDIncludeDirs} ${SDL2_INCLUDE_DIR})
	endif()

	if(UseInternalZLIB)
		set(ZLIBFiles
			"${LIBDir}/zlib/crc32.h"
			"${LIBDir}/zlib/deflate.h"
			"${LIBDir}/zlib/gzguts.h"
			"${LIBDir}/zlib/inffast.h"
			"${LIBDir}/zlib/inffixed.h"
			"${LIBDir}/zlib/inflate.h"
			"${LIBDir}/zlib/inftrees.h"
			"${LIBDir}/zlib/trees.h"
			"${LIBDir}/zlib/zconf.h"
			"${LIBDir}/zlib/zlib.h"
			"${LIBDir}/zlib/zutil.h"

			"${LIBDir}/zlib/adler32.c"
			"${LIBDir}/zlib/compress.c"
			"${LIBDir}/zlib/crc32.c"
			"${LIBDir}/zlib/deflate.c"
			"${LIBDir}/zlib/gzclose.c"
			"${LIBDir}/zlib/gzlib.c"
			"${LIBDir}/zlib/gzread.c"
			"${LIBDir}/zlib/gzwrite.c"
			"${LIBDir}/zlib/infback.c"
			"${LIBDir}/zlib/inffast.c"
			"${LIBDir}/zlib/inflate.c"
			"${LIBDir}/zlib/inftrees.c"
			"${LIBDir}/zlib/trees.c"
			"${LIBDir}/zlib/uncompr.c"
			"${LIBDir}/zlib/zutil.c"
		)
		source_group("zlib" FILES ${ZLIBFiles})
		set(MVMPDEDFiles ${MVMPDEDFiles} ${ZLIBFiles})
	else()
		find_package(ZLIB)
		if(NOT ZLIB_FOUND)
			message(FATAL_ERROR "zlib dev files not found! Install it or set UseInternalZLIB ON")
		endif()
		set(MVMPDEDIncludeDirs ${MVMPDEDIncludeDirs} ${ZLIB_INCLUDE_DIR})
		set(MVMPDEDLibraries ${MVMPDEDLibraries} ${ZLIB_LIBRARY})
	endif()

	# Source
	set(BotlibFiles
		"${SRCDir}/botlib/aasfile.h"
		"${SRCDir}/botlib/be_aas_bsp.h"
		"${SRCDir}/botlib/be_aas_cluster.h"
		"${SRCDir}/botlib/be_aas_debug.h"
		"${SRCDir}/botlib/be_aas_def.h"
		"${SRCDir}/botlib/be_aas_entity.h"
		"${SRCDir}/botlib/be_aas_file.h"
		"${SRCDir}/botlib/be_aas_funcs.h"
		"${SRCDir}/botlib/be_aas_main.h"
		"${SRCDir}/botlib/be_aas_move.h"
		"${SRCDir}/botlib/be_aas_optimize.h"
		"${SRCDir}/botlib/be_aas_reach.h"
		"${SRCDir}/botlib/be_aas_route.h"
		"${SRCDir}/botlib/be_aas_routealt.h"
		"${SRCDir}/botlib/be_aas_sample.h"
		"${SRCDir}/botlib/be_ai_weight.h"
		"${SRCDir}/botlib/be_interface.h"
		"${SRCDir}/botlib/l_crc.h"
		"${SRCDir}/botlib/l_libvar.h"
		"${SRCDir}/botlib/l_log.h"
		"${SRCDir}/botlib/l_memory.h"
		"${SRCDir}/botlib/l_precomp.h"
		"${SRCDir}/botlib/l_script.h"
		"${SRCDir}/botlib/l_struct.h"
		"${SRCDir}/botlib/l_utils.h"

		"${SRCDir}/botlib/be_aas_bspq3.cpp"
		"${SRCDir}/botlib/be_aas_cluster.cpp"
		"${SRCDir}/botlib/be_aas_debug.cpp"
		"${SRCDir}/botlib/be_aas_entity.cpp"
		"${SRCDir}/botlib/be_aas_file.cpp"
		"${SRCDir}/botlib/be_aas_main.cpp"
		"${SRCDir}/botlib/be_aas_move.cpp"
		"${SRCDir}/botlib/be_aas_optimize.cpp"
		"${SRCDir}/botlib/be_aas_reach.cpp"
		"${SRCDir}/botlib/be_aas_route.cpp"
		"${SRCDir}/botlib/be_aas_routealt.cpp"
		"${SRCDir}/botlib/be_aas_sample.cpp"
		"${SRCDir}/botlib/be_ai_char.cpp"
		"${SRCDir}/botlib/be_ai_chat.cpp"
		"${SRCDir}/botlib/be_ai_gen.cpp"
		"${SRCDir}/botlib/be_ai_goal.cpp"
		"${SRCDir}/botlib/be_ai_move.cpp"
		"${SRCDir}/botlib/be_ai_weap.cpp"
		"${SRCDir}/botlib/be_ai_weight.cpp"
		"${SRCDir}/botlib/be_ea.cpp"
		"${SRCDir}/botlib/be_interface.cpp"
		"${SRCDir}/botlib/l_crc.cpp"
		"${SRCDir}/botlib/l_libvar.cpp"
		"${SRCDir}/botlib/l_log.cpp"
		"${SRCDir}/botlib/l_memory.cpp"
		"${SRCDir}/botlib/l_precomp.cpp"
		"${SRCDir}/botlib/l_script.cpp"
		"${SRCDir}/botlib/l_struct.cpp"
	)
	source_group("botlib" FILES ${BotlibFiles})
	set(MVMPDEDFiles ${MVMPDEDFiles} ${BotlibFiles})

	set(MVMPDEDServerFiles
		"${SRCDir}/server/server.h"

		"${SRCDir}/server/sv_bot.cpp"
		"${SRCDir}/server/sv_ccmds.cpp"
		"${SRCDir}/server/sv_client.cpp"
		"${SRCDir}/server/sv_game.cpp"
		"${SRCDir}/server/sv_init.cpp"
		"${SRCDir}/server/sv_main.cpp"
		"${SRCDir}/server/sv_net_chan.cpp"
		"${SRCDir}/server/sv_snapshot.cpp"
		"${SRCDir}/server/sv_world.cpp"
	)
	source_group("server" FILES ${MVMPDEDServerFiles})
	set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDServerFiles})

	set(MVMPDEDGhoulFiles
		"${SRCDir}/ghoul2/G2.h"
		"${SRCDir}/ghoul2/G2_gore.h"
		"${SRCDir}/ghoul2/G2_local.h"
		"${SRCDir}/ghoul2/ghoul2_shared.h"

		"${SRCDir}/ghoul2/G2_API.cpp"
		"${SRCDir}/ghoul2/G2_bolts.cpp"
		"${SRCDir}/ghoul2/G2_bones.cpp"
		"${SRCDir}/ghoul2/G2_misc.cpp"
		"${SRCDir}/ghoul2/G2_surfaces.cpp"
	)
	source_group("ghoul2" FILES ${MVMPDEDGhoulFiles})
	set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDGhoulFiles})

	set(MVMPDEDMeerkatFiles
		"${LIBDir}/meerkat/meerkat.h"

		"${LIBDir}/meerkat/meerkat.c"
	)
	source_group("meerkat" FILES ${MVMPDEDMeerkatFiles})
	set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDMeerkatFiles})

	set(MVMPDEDCommonFiles
		"${SRCDir}/qcommon/GenericParser2.h"
		"${SRCDir}/qcommon/INetProfile.h"
		"${SRCDir}/qcommon/MiniHeap.h"
		"${SRCDir}/qcommon/RoffSystem.h"
		"${SRCDir}/qcommon/chash.h"
		"${SRCDir}/qcommon/cm_local.h"
		"${SRCDir}/qcommon/cm_patch.h"
		"${SRCDir}/qcommon/cm_polylib.h"
		"${SRCDir}/qcommon/cm_public.h"
		"${SRCDir}/qcommon/disablewarnings.h"
		"${SRCDir}/qcommon/game_version.h"
		"${SRCDir}/qcommon/hstring.h"
		"${SRCDir}/qcommon/ioapi.h"
		"${SRCDir}/qcommon/qcommon.h"
		"${SRCDir}/qcommon/qfiles.h"
		"${SRCDir}/qcommon/sstring.h"
		"${SRCDir}/qcommon/strip.h"
		"${SRCDir}/qcommon/tags.h"
		"${SRCDir}/qcommon/unzip.h"
		"${SRCDir}/qcommon/vm_local.h"

		"${SRCDir}/qcommon/CNetProfile.cpp"
		"${SRCDir}/qcommon/GenericParser2.cpp"
		"${SRCDir}/qcommon/RoffSystem.cpp"
		"${SRCDir}/qcommon/cm_load.cpp"
		"${SRCDir}/qcommon/cm_patch.cpp"
		"${SRCDir}/qcommon/cm_polylib.cpp"
		"${SRCDir}/qcommon/cm_shader.cpp"
		"${SRCDir}/qcommon/cm_test.cpp"
		"${SRCDir}/qcommon/cm_trace.cpp"
		"${SRCDir}/qcommon/cmd.cpp"
		"${SRCDir}/qcommon/common.cpp"
		"${SRCDir}/qcommon/cvar.cpp"
		"${SRCDir}/qcommon/files.cpp"
		"${SRCDir}/qcommon/hstring.cpp"
		"${SRCDir}/qcommon/huffman.cpp"
		"${SRCDir}/qcommon/ioapi.c"
		"${SRCDir}/qcommon/md4.cpp"
		"${SRCDir}/qcommon/msg.cpp"
		"${SRCDir}/qcommon/net_chan.cpp"
		"${SRCDir}/qcommon/q_math.cpp"
		"${SRCDir}/qcommon/q_shared.cpp"
		"${SRCDir}/qcommon/strip.cpp"
		"${SRCDir}/qcommon/unzip.cpp"
		"${SRCDir}/qcommon/vm.cpp"
		"${SRCDir}/qcommon/vm_interpreted.cpp"
		"${SRCDir}/qcommon/vm_x86.cpp"
	)
	source_group("qcommon" FILES ${MVMPDEDCommonFiles})
	set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDCommonFiles})

	set(MVMPDEDRendererFiles
		"${SRCDir}/renderer/matcomp.h"
		"${SRCDir}/renderer/mdx_format.h"
		"${SRCDir}/renderer/qgl.h"
		"${SRCDir}/renderer/tr_font.h"
		"${SRCDir}/renderer/tr_local.h"
		"${SRCDir}/renderer/tr_public.h"
		"${SRCDir}/renderer/tr_quicksprite.h"

		"${SRCDir}/renderer/matcomp.c"
		"${SRCDir}/renderer/tr_backend.cpp"
		"${SRCDir}/renderer/tr_ghoul2.cpp"
		"${SRCDir}/renderer/tr_image.cpp"
		"${SRCDir}/renderer/tr_init.cpp"
		"${SRCDir}/renderer/tr_main.cpp"
		"${SRCDir}/renderer/tr_mesh.cpp"
		"${SRCDir}/renderer/tr_model.cpp"
		"${SRCDir}/renderer/tr_shader.cpp"
	)
	source_group("renderer" FILES ${MVMPDEDRendererFiles})
	set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDRendererFiles})

	if(WIN32)
		set(MVMPDEDWIN32Files
			"${SRCDir}/win32/win_local.h"

			"${SRCDir}/win32/win_net.cpp"
			"${SRCDir}/win32/win_shared.cpp"

			"${SRCDir}/win32/q3asm.asm"
		)
		source_group("win32" FILES ${MVMPDEDWIN32Files})
		set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDWIN32Files})
	else()
		set(MVMPDEDUnixFiles
			"${SRCDir}/unix/unix_local.h"

			"${SRCDir}/unix/unix_net.cpp"
			"${SRCDir}/unix/unix_shared.cpp"
		)
		source_group("unix" FILES ${MVMPDEDUnixFiles})
		set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDUnixFiles})

		set(MVMPDEDSysFiles
			"${SRCDir}/sys/con_local.h"
			"${SRCDir}/sys/sys_local.h"

			"${SRCDir}/sys/con_log.cpp"
			"${SRCDir}/sys/con_tty.cpp"
			"${SRCDir}/sys/sys_main.cpp"
		)

		source_group("sys" FILES ${MVMPDEDSysFiles})
		set(MVMPDEDFiles ${MVMPDEDFiles} ${MVMPDEDSysFiles})
	endif()
endif()

# jk2mvmp
if (BuildMVMP)
	set(MVMPFiles ${MVMPDEDFiles})
	set(MVMPIncludeDirs ${MVMPDEDIncludeDirs})
	set(MVMPLibraries ${MVMPDEDLibraries})

	# Libraries
	if(WIN32)
		# OpenAL
		find_library(OpenALLib NAMES "softoal_${Architecture}" PATHS ${LIBDir})
		if(NOT OpenALLib)
			message(FATAL_ERROR "softoal library not found!")
		endif()
		set(MVMPLibraries ${MVMPLibraries} ${OpenALLib})
		set(MVMPIncludeDirs ${MVMPIncludeDirs} "${LIBDir}/OpenAL")
	else()
		# OpenGL
		find_package(OpenGL)
		if(NOT OPENGL_FOUND)
			message(FATAL_ERROR "OpenGL dev files not found!")
		endif()
		set(MVMPIncludeDirs ${MVMPIncludeDirs} ${OPENGL_INCLUDE_DIR})
		set(MVMPLibraries ${MVMPLibraries} ${OPENGL_LIBRARIES})

		# OpenAL
		find_package(OpenAL)
		if(NOT OPENAL_FOUND)
			message(FATAL_ERROR "OpenAL dev files not found!")
		endif()
		set(MVMPIncludeDirs ${MVMPIncludeDirs} ${OPENAL_INCLUDE_DIR})
		set(MVMPLibraries ${MVMPLibraries} ${OPENAL_LIBRARY})

		# SDL2
		set(MVMPLibraries ${MVMPLibraries} ${SDL2_LIBRARY})
	endif()

	# EAX
	set(MVMPIncludeDirs ${MVMPIncludeDirs} "${LIBDir}/eax")

	# JPEG
	if(UseInternalJPEG)
		file(GLOB_RECURSE JPEGFiles "${LIBDir}/jpeg-8c/*.c" "${LIBDir}/jpeg-8c/*.h")
		source_group("jpeg-8c" FILES ${JPEGFiles})
		set(MVMPIncludeDirs ${MVMPIncludeDirs} "${LIBDir}/jpeg-8c")
		set(MVMPFiles ${MVMPFiles} ${JPEGFiles})
	else()
		find_package(JPEG)
		if(NOT JPEG_FOUND)
			message(FATAL_ERROR "libjpeg dev files not found! Install it or set UseInternalJPEG ON")
		endif()
		set(MVMPIncludeDirs ${MVMPIncludeDirs} ${JPEG_INCLUDE_DIR})
		set(MVMPLibraries ${MVMPLibraries} ${JPEG_LIBRARIES})
	endif()

	# PNG
	if(UseInternalPNG)
		set(PNGFiles
			"${LIBDir}/libpng/png.h"
			"${LIBDir}/libpng/pngconf.h"
			"${LIBDir}/libpng/pngdebug.h"
			"${LIBDir}/libpng/pnginfo.h"
			"${LIBDir}/libpng/pnglibconf.h"
			"${LIBDir}/libpng/pngpriv.h"
			"${LIBDir}/libpng/pngstruct.h"

			"${LIBDir}/libpng/png.c"
			"${LIBDir}/libpng/pngerror.c"
			"${LIBDir}/libpng/pngget.c"
			"${LIBDir}/libpng/pngmem.c"
			"${LIBDir}/libpng/pngpread.c"
			"${LIBDir}/libpng/pngread.c"
			"${LIBDir}/libpng/pngrio.c"
			"${LIBDir}/libpng/pngrtran.c"
			"${LIBDir}/libpng/pngrutil.c"
			"${LIBDir}/libpng/pngset.c"
			"${LIBDir}/libpng/pngtrans.c"
			"${LIBDir}/libpng/pngwio.c"
			"${LIBDir}/libpng/pngwrite.c"
			"${LIBDir}/libpng/pngwtran.c"
			"${LIBDir}/libpng/pngwutil.c"
		)
		source_group("libpng" FILES ${PNGFiles})
		set(MVMPIncludeDirs ${MVMPIncludeDirs} "${LIBDir}/libpng")
		set(MVMPFiles ${MVMPFiles} ${PNGFiles})
	else()
		find_package(PNG)
		if(NOT PNG_FOUND)
			message(FATAL_ERROR "libpng dev files not found! Install it or set UseInternalPNG ON")
		endif()
		set(MVMPIncludeDirs ${MVMPIncludeDirs} ${PNG_INCLUDE_DIR})
		set(MVMPLibraries ${MVMPLibraries} ${PNG_LIBRARIES})
	endif()

	# CURL
	if(UseInternalCURL)
		file(GLOB_RECURSE CURLFiles "${LIBDir}/curl/*.c" "${LIBDir}/curl/*.h")
		source_group("curl" FILES ${CURLFiles})
		set(MVMPIncludeDirs ${MVMPIncludeDirs} "${LIBDir}/curl")
		set(MVMPFiles ${MVMPFiles} ${CURLFiles})
	else()
		find_package(CURL)
		if(NOT CURL_FOUND)
			message(FATAL_ERROR "libcurl dev files not found! Install it or set UseInternalCURL ON")
		endif()
		set(MVMPIncludeDirs ${MVMPIncludeDirs} ${CURL_INCLUDE_DIR})
		set(MVMPLibraries ${MVMPLibraries} ${CURL_LIBRARIES})
	endif()

	# Source
	set(MVMPClientFiles
		"${SRCDir}/client/FXExport.h"
		"${SRCDir}/client/FxPrimitives.h"
		"${SRCDir}/client/FxScheduler.h"
		"${SRCDir}/client/FxSystem.h"
		"${SRCDir}/client/FxUtil.h"
		"${SRCDir}/client/client.h"
		"${SRCDir}/client/keys.h"
		"${SRCDir}/client/snd_local.h"
		"${SRCDir}/client/snd_mp3.h"
		"${SRCDir}/client/snd_public.h"

		"${SRCDir}/client/FXExport.cpp"
		"${SRCDir}/client/FxPrimitives.cpp"
		"${SRCDir}/client/FxScheduler.cpp"
		"${SRCDir}/client/FxSystem.cpp"
		"${SRCDir}/client/FxTemplate.cpp"
		"${SRCDir}/client/FxUtil.cpp"
		"${SRCDir}/client/cl_cgame.cpp"
		"${SRCDir}/client/cl_cin.cpp"
		"${SRCDir}/client/cl_console.cpp"
		"${SRCDir}/client/cl_input.cpp"
		"${SRCDir}/client/cl_keys.cpp"
		"${SRCDir}/client/cl_main.cpp"
		"${SRCDir}/client/cl_net_chan.cpp"
		"${SRCDir}/client/cl_parse.cpp"
		"${SRCDir}/client/cl_scrn.cpp"
		"${SRCDir}/client/cl_ui.cpp"
		"${SRCDir}/client/snd_dma.cpp"
		"${SRCDir}/client/snd_mem.cpp"
		"${SRCDir}/client/snd_mix.cpp"
		"${SRCDir}/client/snd_mp3.cpp"
	)
	source_group("client" FILES ${MVMPClientFiles})
	set(MVMPFiles ${MVMPFiles} ${MVMPClientFiles})

	set(MVMPMP3Files
		"${LIBDir}/mp3/config.h"
		"${LIBDir}/mp3/copyright.h"
		"${LIBDir}/mp3/htable.h"
		"${LIBDir}/mp3/jdw.h"
		"${LIBDir}/mp3/l3.h"
		"${LIBDir}/mp3/mhead.h"
		"${LIBDir}/mp3/mp3struct.h"
		"${LIBDir}/mp3/port.h"
		"${LIBDir}/mp3/small_header.h"
		"${LIBDir}/mp3/tableawd.h"

		"${LIBDir}/mp3/cdct.c"
		"${LIBDir}/mp3/csbt.c"
		"${LIBDir}/mp3/csbtb.c"
		"${LIBDir}/mp3/csbtl3.c"
		"${LIBDir}/mp3/cup.c"
		"${LIBDir}/mp3/cupini.c"
		"${LIBDir}/mp3/cupl1.c"
		"${LIBDir}/mp3/cupl3.c"
		"${LIBDir}/mp3/cwin.c"
		"${LIBDir}/mp3/cwinb.c"
		"${LIBDir}/mp3/cwinm.c"
		"${LIBDir}/mp3/hwin.c"
		"${LIBDir}/mp3/l3dq.c"
		"${LIBDir}/mp3/l3init.c"
		"${LIBDir}/mp3/mdct.c"
		"${LIBDir}/mp3/mhead.c"
		"${LIBDir}/mp3/msis.c"
		"${LIBDir}/mp3/towave.c"
		"${LIBDir}/mp3/uph.c"
		"${LIBDir}/mp3/upsf.c"
		"${LIBDir}/mp3/wavep.c"
	)
	source_group("mp3" FILES ${MVMPMP3Files})
	set(MVMPIncludeDirs ${MVMPIncludeDirs} "${LIBDir}/mp3")
	set(MVMPFiles ${MVMPFiles} ${MVMPMP3Files})

	set(MVMPRendererFiles
		"${SRCDir}/renderer/glext.h"
		"${SRCDir}/renderer/tr_WorldEffects.h"

		"${SRCDir}/renderer/tr_WorldEffects.cpp"
		"${SRCDir}/renderer/tr_animation.cpp"
		"${SRCDir}/renderer/tr_bsp.cpp"
		"${SRCDir}/renderer/tr_cmds.cpp"
		"${SRCDir}/renderer/tr_curve.cpp"
		"${SRCDir}/renderer/tr_flares.cpp"
		"${SRCDir}/renderer/tr_font.cpp"
		"${SRCDir}/renderer/tr_light.cpp"
		"${SRCDir}/renderer/tr_marks.cpp"
		"${SRCDir}/renderer/tr_noise.cpp"
		"${SRCDir}/renderer/tr_quicksprite.cpp"
		"${SRCDir}/renderer/tr_scene.cpp"
		"${SRCDir}/renderer/tr_shade.cpp"
		"${SRCDir}/renderer/tr_shade_calc.cpp"
		"${SRCDir}/renderer/tr_shadows.cpp"
		"${SRCDir}/renderer/tr_sky.cpp"
		"${SRCDir}/renderer/tr_surface.cpp"
		"${SRCDir}/renderer/tr_surfacesprites.cpp"
		"${SRCDir}/renderer/tr_world.cpp"
	)
	source_group("renderer" FILES ${MVMPRendererFiles})
	set(MVMPFiles ${MVMPFiles} ${MVMPRendererFiles})

	if(WIN32)
		set(MVMPWIN32Files
			"${SRCDir}/win32/glw_win.h"
			"${SRCDir}/win32/resource.h"

			"${SRCDir}/win32/win_gamma.cpp"
			"${SRCDir}/win32/win_glimp.cpp"
			"${SRCDir}/win32/win_input.cpp"
			"${SRCDir}/win32/win_clmain.cpp"
			"${SRCDir}/win32/win_qgl.cpp"
			"${SRCDir}/win32/win_snd.cpp"
			"${SRCDir}/win32/win_syscon.cpp"
			"${SRCDir}/win32/win_wndproc.cpp"

			"${SRCDir}/win32/mv.rc"
		)
		source_group("win32" FILES ${MVMPWIN32Files})
		set(MVMPFiles ${MVMPFiles} ${MVMPWIN32Files})
	else()
		set(MVMPUnixFiles
			"${SRCDir}/unix/sdl_qgl.h"

			"${SRCDir}/unix/sdl_glimp.cpp"
			"${SRCDir}/unix/sdl_input.cpp"
			"${SRCDir}/unix/sdl_snd.cpp"
		)
		source_group("unix" FILES ${MVMPUnixFiles})
		set(MVMPFiles ${MVMPFiles} ${MVMPUnixFiles})
	endif()

	# Project
	if(WIN32)
		add_executable(${MVMP} WIN32 ${MVMPFiles})
	elseif(APPLE)
		set(MACOSX_BUNDLE_BUNDLE_NAME ${ProjectName})
		set(MACOSX_BUNDLE_DISPLAY_NAME ${ProjectName})
		set(MACOSX_BUNDLE_ICON_FILE "mv.icns")
		set(MVMPFiles ${MVMPFiles} ${RESDir}/mv.icns)

		add_executable(${MVMP} MACOSX_BUNDLE ${MVMPFiles})
		set_source_files_properties(${RESDir}/mv.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
		set_target_properties(${MVMP} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${RESDir}/mv.plist")
	else()
		add_executable(${MVMP} ${MVMPFiles})
	endif()

	if(WIN32)
		# copy over openal dll
		add_custom_command(TARGET ${MVMP} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${LIBDir}/softoal_${Architecture}.dll"
			$<TARGET_FILE_DIR:${MVMP}>
		)
	endif()

	# generate assetsmv.pk3
	add_custom_command(TARGET ${MVMP} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${MVMP}>/base"
		COMMAND ${CMAKE_COMMAND} -E remove "$<TARGET_FILE_DIR:${MVMP}>/base/assetsmv.pk3"
	)

	if(WIN32)
		add_custom_command(TARGET ${MVMP} POST_BUILD
			COMMAND "${CMAKE_SOURCE_DIR}/tools/7za.exe" -tzip a
			"$<TARGET_FILE_DIR:${MVMP}>/base/assetsmv.pk3"
			"${CMAKE_SOURCE_DIR}/assets/*"
		)
	else()
		find_program(ZIP_EXECUTABLE zip)
		if(ZIP_EXECUTABLE)
			add_custom_command(TARGET ${MVMP} POST_BUILD
				# ouned: this is kind of tricky
				COMMAND sh -c \"cd ${CMAKE_SOURCE_DIR}/assets && zip -r $<TARGET_FILE_DIR:${MVMP}>/base/assetsmv.pk3 *\"
			)
		endif()
	endif()

	set_target_properties(${MVMP} PROPERTIES COMPILE_DEFINITIONS_RELEASE "${ReleaseDefines};${GlobalDefines}")
	set_target_properties(${MVMP} PROPERTIES COMPILE_DEFINITIONS_DEBUG "${DebugDefines};${GlobalDefines}")
	set_target_properties(${MVMP} PROPERTIES INCLUDE_DIRECTORIES "${MVMPIncludeDirs}")
	target_link_libraries(${MVMP} ${MVMPLibraries})
	set_target_properties(${MVMP} PROPERTIES PROJECT_LABEL "jk2mvmp")

	# installation
	if(WIN32)
		install(TARGETS ${MVMP} DESTINATION ".")
		install(FILES "${LIBDir}/softoal_${Architecture}.dll" DESTINATION ".")
		install(FILES $<TARGET_FILE_DIR:${MVMP}>/base/assetsmv.pk3 DESTINATION "base")
	elseif(APPLE)
		install(TARGETS ${MVMP} BUNDLE DESTINATION ".")

		# ouned: copy over frameworks into the app
		# for this to work it's required that the SDL2.framework is under ~/Library/Frameworks
        # and SDL2 has to be compiled without @rpath (builds from website are with @rpath)
        SET(APPS "\${CMAKE_INSTALL_PREFIX}/${MVMP}.app")
        install(CODE "
            include(BundleUtilities)
            fixup_bundle(\"${APPS}\" \"\" \"\")
        ")
        #install(FILES $<TARGET_FILE_DIR:${MVMP}>/base/assetsmv.pk3 BUNDLE DESTINATION "Resources/base")
    endif()

    # jk2mvmenu - jk2mvmp doesn't work without it
	add_dependencies(${MVMP} ${MVMENU})
	add_subdirectory("${SRCDir}/menu")
endif()

# jk2mvded
if (BuildMVDED)
	set(MVDEDFiles ${MVMPDEDFiles})
	set(MVDEDIncludeDirs ${MVMPDEDIncludeDirs})
	set(MVDEDLibraries ${MVMPDEDLibraries})

	# Source
	set(MVDEDNullFiles
		"${SRCDir}/null/null_client.cpp"
		"${SRCDir}/null/null_glimp.cpp"
		"${SRCDir}/null/null_input.cpp"
		"${SRCDir}/null/null_renderer.cpp"
		"${SRCDir}/null/null_snddma.cpp"
	)
	source_group("null" FILES ${MVDEDNullFiles})
	set(MVDEDFiles ${MVDEDFiles} ${MVDEDNullFiles})

	if(WIN32)
		set(MVDEDSysFiles
			"${SRCDir}/sys/con_local.h"
			"${SRCDir}/sys/sys_local.h"

			"${SRCDir}/sys/con_log.cpp"
			"${SRCDir}/sys/con_win32.cpp"
			"${SRCDir}/sys/sys_main.cpp"
		)
		source_group("sys" FILES ${MVDEDSysFiles})
		set(MVDEDFiles ${MVDEDFiles} ${MVDEDSysFiles})
	endif()

	# Defines
	set(MVDEDDefines "DEDICATED")

	# Project
	add_executable(${MVDED} ${MVDEDFiles})

	set_target_properties(${MVDED} PROPERTIES COMPILE_DEFINITIONS_RELEASE "${ReleaseDefines};${GlobalDefines};${MVDEDDefines}")
	set_target_properties(${MVDED} PROPERTIES COMPILE_DEFINITIONS_DEBUG "${DebugDefines};${GlobalDefines};${MVDEDDefines}")
	set_target_properties(${MVDED} PROPERTIES INCLUDE_DIRECTORIES "${MVMPIncludeDirs}")
	target_link_libraries(${MVDED} ${MVDEDLibraries})
	set_target_properties(${MVDED} PROPERTIES PROJECT_LABEL "jk2mvded")
endif()