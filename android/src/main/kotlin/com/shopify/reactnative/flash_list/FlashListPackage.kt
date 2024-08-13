package com.shopify.reactnative.flash_list

import com.facebook.react.TurboReactPackage
import com.facebook.react.bridge.NativeModule
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.module.annotations.ReactModule
import com.facebook.react.module.model.ReactModuleInfo
import com.facebook.react.module.model.ReactModuleInfoProvider
import com.facebook.react.turbomodule.core.interfaces.TurboModule
import com.facebook.react.uimanager.ViewManager


class ReactNativeFlashListPackage : TurboReactPackage() {
  override fun createViewManagers(reactContext: ReactApplicationContext): List<ViewManager<*, *>> {
    return listOf(
        AutoLayoutViewManager(),
        CellContainerManager()
    )
  }

    override fun getModule(name: String, reactContext: ReactApplicationContext): NativeModule? {
        return if (name == FlashListModule.NAME) {
            FlashListModule(reactContext)
        } else {
            null
        }
    }

    override fun getReactModuleInfoProvider(): ReactModuleInfoProvider {
        return ReactModuleInfoProvider {
            val moduleInfos: MutableMap<String, ReactModuleInfo> =
                HashMap()
            val moduleClass: Class<out NativeModule?> =
                FlashListModule::class.java
            val reactModule =
                moduleClass.getAnnotation(ReactModule::class.java)
            if (reactModule != null) {
                moduleInfos[reactModule.name] = ReactModuleInfo(
                    reactModule.name,
                    moduleClass.name,
                    true,
                    reactModule.needsEagerInit,
                    reactModule.hasConstants,
                    reactModule.isCxxModule,
                    TurboModule::class.java.isAssignableFrom(moduleClass)
                )
            }
            moduleInfos
        }
    }
}
