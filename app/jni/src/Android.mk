LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := AnimatedTexture.cpp main.cpp AssetManager.cpp AudioManager.cpp Blenster.cpp BoxCollider.cpp Bullet.cpp Button.cpp CircleCollider.cpp Clumster.cpp Collider.cpp Enemy.cpp GameEntity.cpp GameManager.cpp Graphics.cpp InputManager.cpp Level.cpp Monster.cpp PhysEntity.cpp PhysicsManager.cpp Player.cpp PlayScreen.cpp Scoreboard.cpp ScreenManager.cpp Spawner.cpp StartScreen.cpp Texture.cpp Timer.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
