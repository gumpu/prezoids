#ifndef HG_GAME_TEXTURES_H
#define HG_GAME_TEXTURES_H

class LTexture {
    public:
        LTexture();
        ~LTexture();
        LTexture(const LTexture& source) = delete;
        LTexture& operator=(const LTexture& source) = delete;

        bool loadFromFile(const char* path);
        bool loadFromText(const char* text, SDL_Color color);
        void render(int x, int y, SDL_Rect* clip = nullptr);
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        void release();

    private:
        SDL_Texture* m_texture;
        int m_width;
        int m_height;
};

extern SDL_Texture* loadTexture(const char* path);

#endif /* HG_GAME_TEXTURES_H */
