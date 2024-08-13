package com.shopify.reactnative.flash_list

import android.util.Log
import com.facebook.jni.HybridData
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.bridge.RuntimeExecutor
import com.facebook.react.bridge.queue.MessageQueueThread
import com.facebook.react.fabric.FabricUIManager
import com.facebook.react.module.annotations.ReactModule
import com.facebook.react.turbomodule.core.interfaces.CallInvokerHolder
import java.lang.ref.WeakReference


@ReactModule(name = FlashListModule.NAME)
class FlashListModule(context: ReactApplicationContext) : NativeFlashListSpec(context) {
    private var weakReactContext: WeakReference<ReactApplicationContext>? = null

    init {
        this.weakReactContext = WeakReference(context)
    }

    override fun initialize() {
        super.initialize()
        instance = this
    }

    override fun invalidate() {
        super.invalidate()
        instance = null
    }

    override fun getName(): String {
        return NAME
    }

    external fun nativeInstall(
        jsiRuntimeRef: Long,
        jsCallInvokerHolder: CallInvokerHolder?
    ): Boolean

    external fun nativeCallJSFunction(
        jsiRuntimeRef: Long,
        jsCallInvokerHolder: CallInvokerHolder?,
        viewId: String,
    ): Boolean

    private external fun initFabric(
        fabricUIManager: FabricUIManager,
    ): HybridData?

    @ReactMethod(isBlockingSynchronousMethod = true)
    override fun install(): Boolean {
        try {
            val context = weakReactContext!!.get()
            if (context == null) {
                Log.e(NAME, "React Application Context was null!")
                return false
            }

            val jsiRuntimeRef = context.javaScriptContextHolder!!.get()
            val jsCallInvokerHolder = context.catalystInstance.jsCallInvokerHolder
            return nativeInstall(jsiRuntimeRef, jsCallInvokerHolder)
        } catch (exception: Exception) {
            Log.e(NAME, "Failed to initialize flashlist!", exception)
            return false
        }
    }

    fun onLayoutUpdated(id: Int, x: Float, y: Float) {
        try {
            val context = weakReactContext!!.get()
            if (context == null) {
                Log.e(NAME, "React Application Context was null!")
                return
            }

            val jsiRuntimeRef = context.javaScriptContextHolder!!.get()
            val jsCallInvokerHolder = context.catalystInstance.jsCallInvokerHolder
            nativeCallJSFunction(jsiRuntimeRef, jsCallInvokerHolder, id.toString())
        } catch (exception: Exception) {
            Log.e(NAME, "Failed to initialize flashlist!", exception)
        }
    }

    companion object {
        const val NAME: String = "Flashlist"
        var instance: FlashListModule? = null
        init {
            System.loadLibrary("sfl")
        }
    }
}