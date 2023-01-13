package com.worktile.flutter.nestedflutterview

import android.app.Activity
import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.ViewGroup.LayoutParams.MATCH_PARENT
import android.widget.FrameLayout
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentTransaction
import com.worktile.flutter.NestedFlutterView
import io.flutter.FlutterInjector
import io.flutter.embedding.android.ExclusiveAppComponent
import io.flutter.embedding.android.FlutterView
import io.flutter.embedding.engine.FlutterEngine
import io.flutter.embedding.engine.dart.DartExecutor

class MainActivity : AppCompatActivity() {
    private val engine by lazy { FlutterEngine(this) }
    private val nestedFlutterView by lazy { NestedFlutterView(this) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

//        val root = findViewById<FrameLayout>(R.id.layout)
        supportFragmentManager.beginTransaction().replace(R.id.layout, MainFragment()).commit()
    }
}

class MainFragment : Fragment() {
    private lateinit var flutterViewEngine: FlutterViewEngine

    private val root by lazy {
        FrameLayout(requireContext()).apply {
            layoutParams = ViewGroup.LayoutParams(MATCH_PARENT, MATCH_PARENT)
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return root
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        val engine = FlutterEngine(context).apply {
            dartExecutor.executeDartEntrypoint(
                DartExecutor.DartEntrypoint(
                    FlutterInjector.instance().flutterLoader().findAppBundlePath(),
                    "main"
                )
            )
        }
        flutterViewEngine = FlutterViewEngine(engine)
        flutterViewEngine.attachToActivity(requireActivity())

    }

    override fun onDestroy() {
        super.onDestroy()
        flutterViewEngine.detachActivity()
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        val flutterView = NestedFlutterView(view.context)
        flutterViewEngine.attachFlutterView(flutterView)
        root.addView(flutterView)
    }
}