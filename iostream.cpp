#include "minicrt.h"

namespace std {
    stdout_stream::stdout_stream() : ofstream() {
        fp = stdout;
    }

    stdout_stream cout; // fix latter: 不知为什么没有进行全局初始化

    ofstream::ofstream() : fp(0) {
    }

    ofstream::ofstream(const char* filename, ofstream::openmode md) : fp(0) {
        open(filename, md);
    }

    ofstream::~ofstream() {
        close();
    }

    ofstream& ofstream::operator<<(char c) {
        fputc(c, fp);
        return *this;
    }

    ofstream& ofstream::operator<<(int n) {
        fprintf(fp, "%d", n);
        return *this;
    }

    ofstream& ofstream::operator<<(const char* str) {
        fprintf(fp, "%s", str);
        return *this;
    }

    ofstream& ofstream::operator<<( ofstream& (*manip)(ofstream&) ) {
        return manip(*this);
    }

    void ofstream::open(const char* filename, ofstream::openmode md) {
        char mode[4];
        close();
        switch (md) {
            case out | trunc:
                strcpy(mode, "w");
                break;
            case out | in | trunc:
                strcpy(mode, "w+");
            case out | trunc | binary:
                strcpy(mode, "wb");
                break;
            case out | in | trunc | binary:
                strcpy(mode, "wb+");
        }

        fp = fopen(filename, mode);
    }

    void ofstream::close() {
        if (fp) {
            fclose(fp);
            fp = 0;
        }
    }

    ofstream& ofstream::write(const char* buf, unsigned size) {
        fwrite(buf, 1, size, fp);
        return *this;
    }

    ofstream& operator<<(ofstream& o, const string& s) {
        return o << s.c_str();
    }
}
