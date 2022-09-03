#include "Image.h"
#include <math.h>
#include <vector>
#include <cstdlib>

void Image::lighten() {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).l + 0.1 > 1) {
                cs225::PNG::getPixel(i, j).l = 1;
            } else {
                cs225::PNG::getPixel(i, j).l += 0.1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).l + amount < 0) {
                continue;
            } else if (cs225::PNG::getPixel(i, j).l + amount > 1) {
                cs225::PNG::getPixel(i, j).l = 1;
            } else {
                cs225::PNG::getPixel(i, j).l += amount;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).l - 0.1 < 0) {
                cs225::PNG::getPixel(i, j).l = 0;
            } else {
                cs225::PNG::getPixel(i, j).l -= 0.1;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).l - amount > 1) {
                continue;
            } else if (cs225::PNG::getPixel(i, j).l - amount < 0) {
                cs225::PNG::getPixel(i, j).l = 0;
            } else {
                cs225::PNG::getPixel(i, j).l -= amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).s + 0.1 > 1) {
                cs225::PNG::getPixel(i, j).s = 1;
            } else {
                cs225::PNG::getPixel(i, j).s += 0.1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).s + amount > 1) {
                cs225::PNG::getPixel(i, j).s = 1;
            } else {
                cs225::PNG::getPixel(i, j).s += amount;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).s - 0.1 < 0) {
                cs225::PNG::getPixel(i, j).s = 0;
            } else {
                cs225::PNG::getPixel(i, j).s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).s - amount < 0) {
                cs225::PNG::getPixel(i, j).s = 0;
            } else {
                cs225::PNG::getPixel(i, j).s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            cs225::PNG::getPixel(i, j).s = 0;
        }
    }
}

// need to fix
void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            if (cs225::PNG::getPixel(i, j).h + degrees > 360) {
                cs225::PNG::getPixel(i, j).h = cs225::PNG::getPixel(i, j).h + degrees ;
                while (cs225::PNG::getPixel(i, j).h > 360) {
                    cs225::PNG::getPixel(i, j).h -= 360;
                }
            } else if (cs225::PNG::getPixel(i, j).h + degrees < 0) {

            } else {
                cs225::PNG::getPixel(i, j).h = cs225::PNG::getPixel(i, j).h + degrees;
            }
        }
    }
}

void Image::ililnify() {
    for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
        for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
            cs225::PNG::getPixel(i, j).h = findClosest(cs225::PNG::getPixel(i, j).h);
        }
    }
}

int Image::findClosest(double x) {
    double orange = abs(x - 11);
    double blue = abs(x - 216);
    if (orange < blue) {
        return 11;
    } else {
        return 216;
    }
}

void Image::scale(double factor) {
    if (factor == 1) {
        return;
    } 
    cs225::PNG new_image = cs225::PNG(round(factor * cs225::PNG::width()), round(factor * cs225::PNG::height()));
    if (factor > 1) {
        for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
            for (unsigned int j = 0; j < cs225::PNG::width(); ++j) {
                for (unsigned int k = round(factor); k >= 0; --k) {
                    if (j + k >= new_image.width()) {
                        continue;
                    } else {
                        new_image.getPixel(i, j + k) = cs225::PNG::getPixel(i, j);
                    }
                }
                for (unsigned int k = round(factor); k >= 0; --k) {
                    if (i + k >= new_image.height()) {
                        continue;
                    } else {
                        new_image.getPixel(i + k, j) = cs225::PNG::getPixel(i, j);
                    }
                }
            }
        }
    } else {
        std::vector<cs225::HSLAPixel> vec;
        int k = factor;
        int l = 0;
        for (unsigned int i = 0; i < cs225::PNG::height(); ++i) {
            for (unsigned int j = 0; j < cs225::PNG::width(); ++j) { 
                if (k > 1) {
                    vec.push_back(cs225::PNG::getPixel(i, j));
                    k -= 1;
                }
            }
        }
        for (unsigned int i = 0; i < new_image.height(); ++i) {
            for (unsigned int j = 0; j < new_image.width(); ++j) {
                new_image.getPixel(i, j) = vec.at(l);
                ++l;
            }
        }
    }
    cs225::PNG::resize(round(factor * cs225::PNG::width()), round(factor * cs225::PNG::height()));
    for (unsigned int i = 0; i < new_image.height(); ++i) {
        for (unsigned int j = 0; j < new_image.width(); ++j) {
            cs225::PNG::getPixel(i, j) = new_image.getPixel(i, j);
        }
    }
}

int Image::gcd(int a, int b) {
    while (b > 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

void Image::scale(unsigned w, unsigned h) {

    unsigned int height = cs225::PNG::height();
    unsigned int width = cs225::PNG::width();

    if ((cs225::PNG::width()/cs225::PNG::height()) > 1) {
        width = w;
        if (cs225::PNG::height() < h) {
            while (height < h) {
                if ((width/height) == (cs225::PNG::width()/cs225::PNG::height())) {
                    scale(h/cs225::PNG::height());
                } else {
                    ++height;
                }
            }
        } else {
            while (height > h) {
                if ((width/height) == (cs225::PNG::width()/cs225::PNG::height())) {
                    scale(h/cs225::PNG::height());
                } else {
                    --height;
                }
            }
        }
    } else if ((cs225::PNG::width()/cs225::PNG::height()) < 1) {
        height = h;
        if (cs225::PNG::width() < w) {
            while (width < w) {
                if ((width/height) == (cs225::PNG::width()/cs225::PNG::height())) {
                    scale(w/cs225::PNG::width());
                } else {
                    ++width;
                }
            }
        } else {
            while (width > w) {
                if ((width/height) == (cs225::PNG::width()/cs225::PNG::height())) {
                    scale(w/cs225::PNG::width());
                } else {
                    --width;
                }
            }
        }
    } else {
        if (cs225::PNG::width() < w) {
            scale(w/cs225::PNG::width());
        } else {
            scale(cs225::PNG::width()/w);
        }
    }
}