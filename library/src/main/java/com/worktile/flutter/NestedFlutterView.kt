package com.worktile.flutter

import android.annotation.SuppressLint
import android.content.Context
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.VelocityTracker
import android.view.ViewConfiguration
import androidx.core.view.*
import androidx.core.view.ViewCompat.TYPE_TOUCH
import io.flutter.embedding.android.FlutterImageView
import io.flutter.embedding.android.FlutterSurfaceView
import io.flutter.embedding.android.FlutterTextureView
import io.flutter.embedding.android.FlutterView
import io.flutter.embedding.engine.FlutterEngine
import io.flutter.plugin.common.BasicMessageChannel
import io.flutter.plugin.common.StandardMessageCodec

/**
 * 一个android app进程有一个libnested_flutter_view.so
 * 一个android app进程（libnested_flutter_view.so）可能有多个NestedFlutterView
 * 一个android app进程（libnested_flutter_view.so）可能有多个Flutter Engine(Dart VM)
 * 一个NestedFlutterView一个时刻会有0或1个Flutter Engine(Dart VM)
 */
typealias CopyNestedScrollingChildHelper = com.worktile.flutter.NestedScrollingChildHelper
typealias NestedScrollingChildHelper = androidx.core.view.NestedScrollingChildHelper

class NestedFlutterView : FlutterView, NestedScrollingChild, NestedScrollingChild2,
    NestedScrollingChild3 {
    constructor(context: Context) : super(context)
    constructor(context: Context, flutterSurfaceView: FlutterSurfaceView) : super(
        context,
        flutterSurfaceView
    )

    constructor(context: Context, flutterTextureView: FlutterTextureView) : super(
        context,
        flutterTextureView
    )

    constructor(context: Context, flutterImageView: FlutterImageView) : super(
        context,
        flutterImageView
    )

    constructor(context: Context, attrs: AttributeSet) : super(context, attrs)

    companion object {
        init {
            System.loadLibrary("nested_flutter_view")
        }
    }

    private val nestedScrollingChildHelper by lazy { NestedScrollingChildHelper(this) }

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
    }

    override fun attachToFlutterEngine(flutterEngine: FlutterEngine) {
        super.attachToFlutterEngine(flutterEngine)
        handlerChannel.send(handler)
    }

    override fun detachFromFlutterEngine() {
        handlerChannel.send(0)
        super.detachFromFlutterEngine()
    }

    private var lastTouchX = 0
    private var lastTouchY = 0
    private var scrollPointerId = 0
    private val nestedOffset = arrayOf(0, 0).toIntArray()
    private val velocityTracker by lazy { VelocityTracker.obtain() }
    private var xVelocity = 0f
    private var yVelocity = 0f

    override fun onInterceptTouchEvent(ev: MotionEvent?): Boolean {
        velocityTracker.addMovement(ev)
        return super.onInterceptTouchEvent(ev)
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onTouchEvent(event: MotionEvent): Boolean {
        var eventAddedToVelocityTracker = false
        if (event.actionMasked == MotionEvent.ACTION_DOWN) {
            nestedOffset[0] = 0
            nestedOffset[1] = 0
        }
        val velocityMotionEvent = MotionEvent.obtain(event)
        velocityMotionEvent.offsetLocation(
            nestedOffset[0].toFloat(),
            nestedOffset[1].toFloat()
        )

        when (event.actionMasked) {
            MotionEvent.ACTION_DOWN -> {
                scrollPointerId = event.getPointerId(0)
            }

            MotionEvent.ACTION_POINTER_DOWN -> {
                scrollPointerId = event.getPointerId(event.actionIndex)
            }

            MotionEvent.ACTION_POINTER_UP -> {
                val actionIndex = event.actionIndex
                if (event.getPointerId(actionIndex) == scrollPointerId) {
                    val newIndex = if (actionIndex == 0) 1 else 0
                    scrollPointerId = event.getPointerId(newIndex)
                }
            }

            MotionEvent.ACTION_UP -> {
                velocityTracker.addMovement(velocityMotionEvent)
                eventAddedToVelocityTracker = true
                velocityTracker.computeCurrentVelocity(
                    1000,
                    ViewConfiguration.get(context).scaledMaximumFlingVelocity.toFloat()
                )
                xVelocity = -velocityTracker.getXVelocity(scrollPointerId)
                yVelocity = -velocityTracker.getYVelocity(scrollPointerId)
                velocityTracker.clear()
            }
        }

        if (!eventAddedToVelocityTracker) {
            velocityTracker.addMovement(velocityMotionEvent)
        }
        velocityMotionEvent.recycle()

        return super.onTouchEvent(event)
    }

    fun getYVelocity(): Float {
        return yVelocity.apply {
            yVelocity = 0f
        }
    }

    override fun setNestedScrollingEnabled(enabled: Boolean) {
        nestedScrollingChildHelper.isNestedScrollingEnabled = enabled
    }

    override fun isNestedScrollingEnabled(): Boolean {
        return nestedScrollingChildHelper.isNestedScrollingEnabled
    }

    override fun hasNestedScrollingParent(): Boolean {
        return nestedScrollingChildHelper.hasNestedScrollingParent()
    }

    override fun hasNestedScrollingParent(type: Int): Boolean {
        return nestedScrollingChildHelper.hasNestedScrollingParent(type)
    }

    override fun startNestedScroll(axes: Int): Boolean {
        return nestedScrollingChildHelper.startNestedScroll(axes)
    }

    override fun startNestedScroll(axes: Int, type: Int): Boolean {
        return nestedScrollingChildHelper.startNestedScroll(axes, type)
    }

    override fun stopNestedScroll() {
        nestedScrollingChildHelper.stopNestedScroll()
    }

    override fun stopNestedScroll(type: Int) {
        nestedScrollingChildHelper.stopNestedScroll(type)
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
        nestedScrollingChildHelper.dispatchNestedScroll(
            dxConsumed,
            dyConsumed,
            dxUnconsumed,
            dyUnconsumed,
            offsetInWindow,
            type,
            consumed
        )
        nestedOffset[0] += offsetInWindow?.get(0) ?: 0
        nestedOffset[1] += offsetInWindow?.get(1) ?: 0
    }

    override fun dispatchNestedScroll(
        dxConsumed: Int,
        dyConsumed: Int,
        dxUnconsumed: Int,
        dyUnconsumed: Int,
        offsetInWindow: IntArray?,
        type: Int
    ): Boolean {
        val result = nestedScrollingChildHelper.dispatchNestedScroll(
            dxConsumed,
            dyConsumed,
            dxUnconsumed,
            dyUnconsumed,
            offsetInWindow,
            type
        )
        nestedOffset[0] += offsetInWindow?.get(0) ?: 0
        nestedOffset[1] += offsetInWindow?.get(1) ?: 0
        return result
    }

    override fun dispatchNestedPreScroll(
        dx: Int,
        dy: Int,
        consumed: IntArray?,
        offsetInWindow: IntArray?,
        type: Int
    ): Boolean {
        val result = nestedScrollingChildHelper.dispatchNestedPreScroll(
            dx,
            dy,
            consumed,
            offsetInWindow,
            type
        )
        nestedOffset[0] += offsetInWindow?.get(0) ?: 0
        nestedOffset[1] += offsetInWindow?.get(1) ?: 0
        return result
    }

    fun requestParentDisallowInterceptTouchEvent(disallowIntercept: Boolean) {
        parent.requestDisallowInterceptTouchEvent(disallowIntercept)
    }

    private external fun flutterViewHandler(): Long
    private external fun deleteFlutterViewHandler(handler: Long)

}