package com.worktile.flutter

import android.content.Context
import android.util.AttributeSet
import androidx.core.view.NestedScrollingChild
import androidx.core.view.NestedScrollingChild2
import androidx.core.view.NestedScrollingChild3
import io.flutter.embedding.android.FlutterImageView
import io.flutter.embedding.android.FlutterSurfaceView
import io.flutter.embedding.android.FlutterTextureView
import io.flutter.embedding.android.FlutterView
import io.flutter.embedding.engine.renderer.FlutterUiDisplayListener
import io.flutter.plugin.common.BasicMessageChannel
import io.flutter.plugin.common.StandardMessageCodec

/**
 * 一个android app进程有一个libnested_flutter_view.so
 * 一个android app进程（libnested_flutter_view.so）可能有多个NestedFlutterView
 * 一个android app进程（libnested_flutter_view.so）可能有多个Flutter Engine(Dart VM)
 * 一个NestedFlutterView一个时刻会有0或1个Flutter Engine(Dart VM)
 */
class NestedFlutterView : FlutterView, NestedScrollingChild, NestedScrollingChild2,
    NestedScrollingChild3 {
    constructor(context: Context) : super(context)
    constructor(context: Context, flutterSurfaceView: FlutterSurfaceView) : super(context, flutterSurfaceView)
    constructor(context: Context, flutterTextureView: FlutterTextureView) : super(context, flutterTextureView)
    constructor(context: Context, flutterImageView: FlutterImageView) : super(context, flutterImageView)
    constructor(context: Context, attrs: AttributeSet) : super(context, attrs)

    companion object {
        init {
            System.loadLibrary("nested_flutter_view")
        }
    }

    private val handler by lazy { flutterViewHandler() }

    private val handlerChannel by lazy {
        BasicMessageChannel(
            binaryMessenger,
            "com.worktile.flutter.nested_flutter_view/handler",
            StandardMessageCodec.INSTANCE
        )
    }

    init {
        isNestedScrollingEnabled = true
        addOnFirstFrameRenderedListener(object : FlutterUiDisplayListener {
            override fun onFlutterUiDisplayed() {
                handlerChannel.send(handler)
            }

            override fun onFlutterUiNoLongerDisplayed() { }
        })
    }

    override fun detachFromFlutterEngine() {
        deleteFlutterViewHandler(handler)
        super.detachFromFlutterEngine()
    }

    override fun startNestedScroll(axes: Int, type: Int): Boolean {
        TODO("Not yet implemented")
    }

    override fun stopNestedScroll(type: Int) {
        TODO("Not yet implemented")
    }

    override fun hasNestedScrollingParent(type: Int): Boolean {
        TODO("Not yet implemented")
    }

    override fun dispatchNestedScroll(
        dxConsumed: Int,
        dyConsumed: Int,
        dxUnconsumed: Int,
        dyUnconsumed: Int,
        offsetInWindow: IntArray?,
        type: Int,
        consumed: IntArray
    ) {
        TODO("Not yet implemented")
    }

    override fun dispatchNestedScroll(
        dxConsumed: Int,
        dyConsumed: Int,
        dxUnconsumed: Int,
        dyUnconsumed: Int,
        offsetInWindow: IntArray?,
        type: Int
    ): Boolean {
        TODO("Not yet implemented")
    }

    override fun dispatchNestedPreScroll(
        dx: Int,
        dy: Int,
        consumed: IntArray?,
        offsetInWindow: IntArray?,
        type: Int
    ): Boolean {
        TODO("Not yet implemented")
    }

    override fun dispatchNestedPreFling(velocityX: Float, velocityY: Float): Boolean {
        println("dispatchNestedPreFlingggggggggggggggggggggggg")
        return super.dispatchNestedPreFling(velocityX, velocityY)
    }

    fun testResultArray(array: IntArray): Int {
        array[0] = 1
        array[1] = 2
        return 6
    }

    private external fun flutterViewHandler(): Long
    private external fun deleteFlutterViewHandler(handler: Long)

}