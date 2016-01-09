EXEC=binarytree
LIBS=lib${EXEC}.so
CC=gcc
CFLAGS=-w
CFLAGS_O=-c -w -fPIC
CFLAGS_LIB=-shared
CFLAGS_LIB_LD=-soname,${LIBS}
CFLAGS_LD=-rpath,.
LDFLAGS=-L. -l${EXEC}

EXEC_DBG=binarytree-dbg
LIBS_DBG=lib${EXEC_DBG}.so
CFLAGS_DBG=-g -Wall
CFLAGS_LIB_LD_DBG=-soname,${LIBS_DBG}
LDFLAGS_DBG=-L. -l${EXEC_DBG}

all:${EXEC}
${EXEC}:${LIBS} binary_tree_driver.c
	${CC} ${CFLAGS} binary_tree_driver.c -o ${EXEC} -Wl,${CFLAGS_LD} ${LDFLAGS}
${LIBS}:binary_tree.o
	${CC} ${CFLAGS_LIB} -Wl,${CFLAGS_LIB_LD} binary_tree.o -o ${LIBS}.1.0
	ln -sf ${LIBS}.1.0 ${LIBS}.1
	ln -sf ${LIBS}.1 ${LIBS}
binary_tree.o:binary_tree_c.h binary_tree_c.c
	${CC} ${CFLAGS_O} binary_tree_c.c -o binary_tree.o
debug:${EXEC_DBG}
${EXEC_DBG}:${LIBS_DBG} binary_tree_driver.c
	${CC} ${CFLAGS_DBG} binary_tree_driver.c -o ${EXEC_DBG} -Wl,${CFLAGS_LD} ${LDFLAGS_DBG}
${LIBS_DBG}:binary_tree-dbg.o
	${CC} ${CFLAGS_LIB} -Wl,${CFLAGS_LIB_LD_DBG} binary_tree-dbg.o -o ${LIBS_DBG}.1.0
	ln -sf ${LIBS_DBG}.1.0 ${LIBS_DBG}.1
	ln -sf ${LIBS_DBG}.1 ${LIBS_DBG}
binary_tree-dbg.o:binary_tree_c.h binary_tree_c.c
	${CC} ${CFLAGS_O} ${CFLAGS_DBG} binary_tree_c.c -o binary_tree-dbg.o
.PHONY:clean
clean:
	rm *.o
.PHONY:distclean
distclean: clean
	rm *.so*
	rm ${EXEC}
	rm ${EXEC_DBG}
