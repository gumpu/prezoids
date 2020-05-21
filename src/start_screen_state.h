#ifndef HG_START_SCREEN_STATE_H
#define HG_START_SCREEN_STATE_H

class StartScreenState {
    public:
        StartScreenState();
        ~StartScreenState();
        StartScreenState(const StartScreenState& source);
        StartScreenState& operator=(const StartScreenState& source);
        void render(Camera& camera);
    private:
        SDL_Texture* m_background;
        LTexture m_text_texture;
        char m_buffer[80];
        int m_frame;
};

#endif /* HG_START_SCREEN_STATE_H */
