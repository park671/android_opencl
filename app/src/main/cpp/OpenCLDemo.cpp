//
//  sonyOpenCLexample.cpp
//  OpenCL Example
//
//  Created by Rasmusson, Jim on 18/03/13.
//
//  Copyright (c) 2013, Sony Mobile Communications AB
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of Sony Mobile Communications AB nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <stdio.h>

#include <android/bitmap.h>

#include "refNR.h"
#include "openCLNR.h"
#include <jni.h>
#include <jni.h>

extern "C" jint
Java_com_example_opencl_MainActivity_runNativeC(JNIEnv *env, jclass clazz, jobject bmp_in,
                                                jobject bmp_out, jintArray info) {
    void *bi;
    void *bo;

    jint *i = env->GetIntArrayElements(info, NULL);

    AndroidBitmap_lockPixels(env, bmp_in, &bi);
    AndroidBitmap_lockPixels(env, bmp_out, &bo);

    refNR((unsigned char *) bi, (unsigned char *) bo, (int *) i);

    AndroidBitmap_unlockPixels(env, bmp_in);
    AndroidBitmap_unlockPixels(env, bmp_out);
    env->ReleaseIntArrayElements(info, i, 0);

    return 0;
}

extern "C" jint
Java_com_example_opencl_MainActivity_runOpenCL(JNIEnv *env, jclass clazz, jobject bmp_in,
                                               jobject bmp_out, jintArray info) {
    void *bi;
    void *bo;

    jint *i = env->GetIntArrayElements(info, NULL);

    AndroidBitmap_lockPixels(env, bmp_in, &bi);
    AndroidBitmap_lockPixels(env, bmp_out, &bo);

    openCLNR((unsigned char *) bi, (unsigned char *) bo, (int *) i);

    AndroidBitmap_unlockPixels(env, bmp_in);
    AndroidBitmap_unlockPixels(env, bmp_out);
    env->ReleaseIntArrayElements(info, i, 0);

    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_opencl_MainActivity_addByOpenCL(JNIEnv *env, jclass clazz, jintArray array1,
                                                 jintArray array2, jint size) {
    int *a = env->GetIntArrayElements(array1, JNI_FALSE);
    int *b = env->GetIntArrayElements(array2, JNI_FALSE);

    openCLAdd(a, b, size);

    env->ReleaseIntArrayElements(array1, a, 0);
    env->ReleaseIntArrayElements(array2, b, 0);
    return 0;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_opencl_MainActivity_isSameOpenCL(JNIEnv *env, jclass clazz, jintArray array1,
                                                  jintArray array2, jint size) {
    int *a = env->GetIntArrayElements(array1, JNI_FALSE);
    int *b = env->GetIntArrayElements(array2, JNI_FALSE);
    int result = 0;
    openCLSame(a, b, &result, size);
    env->ReleaseIntArrayElements(array1, a, 0);
    env->ReleaseIntArrayElements(array2, b, 0);
    return result;
}