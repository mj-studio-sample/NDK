package happy.mjstudio.ndk

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    private val TAG = MainActivity::class.java.simpleName

    private val native = NativeLib()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        native.addCallback(object : Callback {
            override fun onStringReversed(str: String) {
                reverseText2.text = str
            }
        })

        reverse.setOnClickListener {
            reverseText.text = native.reverseString(original.text.toString())
        }

        reverse2.setOnClickListener {
            native.reverseStringWithCallback(original2.text.toString())
        }
    }
}
