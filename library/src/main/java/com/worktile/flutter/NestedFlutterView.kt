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
import io.flutter.embedding.engine.FlutterEngine

class NestedFlutterView : FlutterView, NestedScrollingChild, NestedScrollingChild2,
    NestedScrollingChild3 {
    constructor(context: Context) : super(context)
    constructor(context: Context, flutterSurfaceView: FlutterSurfaceView) : super(context, flutterSurfaceView)
    constructor(context: Context, flutterTextureView: FlutterTextureView) : super(context, flutterTextureView)
    constructor(context: Context, flutterImageView: FlutterImageView) : super(context, flutterImageView)
    constructor(context: Context, attrs: AttributeSet) : super(context, attrs)

    init {
        isNestedScrollingEnabled = true
    }

    override fun attachToFlutterEngine(flutterEngine: FlutterEngine) {
        super.attachToFlutterEngine(flutterEngine)
        initAfterAttachedToEngine()
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

    external fun initAfterAttachedToEngine()

}