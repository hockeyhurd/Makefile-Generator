/**
 * @author hockeyhurd
 * @version 5/8/18
 */

#include "filesystem.h"
#include "dirent.h"

#include <sys/stat.h>
#include <string>

#if OS_WIN
#include <direct.h>
inline static char *getcwd(char *buf, s32 len) {
    return _getcwd(buf, len);
}
#else
#include <unistd.h>
#endif

#if 0
static char *toFileMode(const EFileOp op) {
    switch (op) {
        case EFILE_OP_READ:
            return "r";
        case EFILE_OP_WRITE:
            return "w";
        case EFILE_OP_OVERWRITE:
            return "w+";
        default:
#if Debug
            perror("Error unknown mode!\n");
            exit(-1);
#endif
            return nullptr;
    }
}
#else
static std::string toFileMode(const EFileOp op) {
    switch (op) {
        case EFILE_OP_READ:
            return "r";
        case EFILE_OP_WRITE:
            return "w";
        case EFILE_OP_OVERWRITE:
            return "w+";
        default:
#if Debug
            perror("Error unknown mode!\n");
            exit(-1);
#endif
            return "";
    }
}
#endif

static char workingDirBuf[1024];

char *getCurrentWorkingDir(void) {
    if (getcwd(workingDirBuf, sizeof(workingDirBuf)) != nullptr)
        return workingDirBuf;

    return nullptr;
}

b32 checkIfFileExists(const char *path) {
    struct stat s;
    return path != nullptr && stringLength(path) && stat(path, &s) == 0 ? True : False;
}

u32 openFile(File *file) {
    /*char *mode = toFileMode(file->op);

    if (mode == nullptr)
        return 1;*/

    std::string mode = toFileMode(file->op);

    file->file = fopen(file->path.cstr, mode.c_str());

    if (file->file == nullptr) {
        // perror("Error openning file!\n");
		fprintf(stderr, "Error openning file: '%s'!\n", file->path.cstr);
        return 1;
    }

    struct stat s;

    if (stat(file->path.cstr,&s) == 0) {
        file->isDir = s.st_mode & S_IFDIR ? True : False;
    }

    else {
        perror("Error determining whether is a directory!\n");
        return 1;
    }

    return 0;
}

void closeFile(File *file) {
    fclose(file->file);
    file->file = nullptr;
}

u32 readByteFromFile(const File *file) {
    return (u32) getc(file->file);
}

u32 readIntFromFile(const File *file, const b32 bigEndian) {
    u32 output;

    if (bigEndian) {
        output = (u32) getc(file->file);
        output <<= 8;
        output |= getc(file->file);
        output <<= 8;
        output |= getc(file->file);
        output <<= 8;
        output |= getc(file->file);
    }

    else {
        output = (u32) getc(file->file);
        output |= getc(file->file) << 0x8;
        output |= getc(file->file) << 0x10;
        output |= getc(file->file) << 0x18;
    }

    return output;
}

void writeByteToFile(const u32 data, const File *file) {
    putc(data, file->file);
}

void writeIntToFile(const u32 data, const File *file, const b32 bigEndian) {
    if (bigEndian) {
        putc(data >> 0x18, file->file);
        putc((data >> 0x10) & 0xFF, file->file);
        putc((data >> 0x8) & 0xFF, file->file);
        putc(data & 0xFF, file->file);
    }

    else {
        u32 copy = data;

        putc(copy & 0xFF, file->file);
        copy >>= 8;

        putc(copy & 0xFF, file->file);
        copy >>= 8;

        putc(copy & 0xFF, file->file);
        copy >>= 8;

        putc(copy & 0xFF, file->file);
    }
}

b32 openDir(Dir *dir) {
	if (dir == nullptr || dir->op == EDIR_OP_VALID)
		return False;

	dir->dir = (DIR *) opendir(dir->path.cstr);

	if (dir->dir == nullptr) {
		fprintf(stderr, "Error openning directory: '%s'!\n", dir->path.cstr);
		return False;
	}

	return True;
}

void closeDir(Dir *dir) {
	if (dir != nullptr && dir->dir != nullptr && dir->op == EDIR_OP_VALID) {
		closedir((DIR *) dir->dir);
		dir->dir = nullptr;
		dir->op = EDIR_OP_INVALID;
	}
}

#if 0
u32 getFilesAndSubdirectories(const Dir *dir, const ArrayList *list) {
	if (dir == nullptr || dir->dir == nullptr || dir->op != EDIR_OP_VALID || list == nullptr) {
		// fprintf(stderr, "Error reading files and subdirectories!\n");
		perror("Error reading files and subdirectories!\n");
		return 1;
	}

	struct dirent *entry;

	while ((entry = readdir((DIR *) dir->dir)) != nullptr) {
		String *currentFile = (String *) myMalloc(sizeof(String), "Construct file/dir name");
		constructString(currentFile, entry->d_name);

		addArrayList((ArrayList *) list, currentFile);
	}

	return 0;
}

void cleanupDirectoryListing(const ArrayList *list) {
	if (list == nullptr || !list->len)
		return;

	ArrayListIterator iter;
	constructArrayListIterator(&iter, list);

	while (hasNextArrayListIterator(&iter)) {
		String *file = (String *) nextArrayListIterator(&iter);
		desrtuctString(file);
		myFree(file, "Free file!");
	}
}
#endif
