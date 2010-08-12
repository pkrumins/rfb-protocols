#ifndef HEXTILE_H
#define HEXTILE_H

class Update {
public:
    void decode(unsigned char *screen) = 0;
};

class RectUpdate : public Update {
    unsigned char *buf;
    int x, y, w, h;
public:
    RectUpdate(unsigned char *bbuf, int llen, int xx, int yy, int ww, int hh);
    ~RectUpdate();
    void decode(unsigned char *screen, int screen_width, int screen_height);
};

class ColorRect : public Update {
    unsigned int color;
    int x, y, w, h;
public:
    ColorRect(unsigned int ccolor, int xx, int yy, int ww, int hh);
    void decode(unsigned char *screen, int screen_width, int screen_height);
};

class FgBgRect : public Update {
public:
    FgBgRect(unsigned int fg_color, unsigned int bg_color, int xx, int yy, int ww, int hh);
    void decode(unsigned char *screen, int screen_width, int screen_height);
};

class HextileDecoder {
    int width, height;
    unsigned int bg_color;
    unsigned int fg_color;

    typedef std::vector<Update *> VectorUpdates;
    VectorUpdates updates;

    unsigned char *screen;
public:
    HextileDecoder(int wwidth, int hheight);
    ~HextileDecoder(int wwidth, int hheight);

    void rect(unsigned char *bbuf, int xx, int yy, int ww, int hh);
    void color_rect(unsigned int ccolor, int xx, int yy, int ww, int hh);
    void fgbg_rect(int xx, int yy, int ww, int hh);
    void set_background(unsigned int ccolor);
    void set_foreground(unisnged int ccolor);

    void decode();

    const unsigned char *get() const;
    int get_len() const;
};

#endif

