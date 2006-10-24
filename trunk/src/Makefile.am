INCLUDES = \
	-DLOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\" 		\
	-DDATADIR=\""$(datadir)"\" 					\
	-DHIPPO_DATADIR=\""$(datadir)/hippopotamus"\" 					\
	-DHIPPO_IMAGEDIR=\""$(datadir)/pixmaps/hippopotamus"\" 		\
	-DIMAGEDIR=\""$(datadir)/pixmaps"\" 				\
	$(PACKAGE_CFLAGS)

bin_PROGRAMS = hippopotamus

hippopotamus_SOURCES = 		\
	hippo.c			\
	hippo.h			\
	hippo_preferences.c	\
	hippo_preferences.h	\
	hippo_streamer.c	\
	hippo_streamer.h

hippopotamus_LDFLAGS = 

hippopotamus_LDADD =  \
	$(PACKAGE_LIBS)

