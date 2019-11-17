package happy.mjstudio.ndk

/**
 * Created by mj on 17, November, 2019
 */

interface Callback {
    fun onStringReversed(str: String)
}

class NativeLib : Callback {

    private val TAG = NativeLib::class.java.simpleName

    companion object {
        init {
            System.loadLibrary("native")
        }
    }

    private val callbacks = mutableListOf<Callback>()

    fun addCallback(callback: Callback) {
        callbacks.add(callback)
    }

    fun removeCallback(callback: Callback): Boolean {
        return callbacks.remove(callback)
    }


    external fun printLog()

    external fun returnString(): String

    external fun reverseString(str: String): String

    external fun reverseStringWithCallback(str: String)

    override fun onStringReversed(str: String) {
        callbacks.forEach {
            it.onStringReversed(str)
        }
    }
}