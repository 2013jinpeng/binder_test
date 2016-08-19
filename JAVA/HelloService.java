
import android.util.Log;
import java.lang.String;

public class HelloService extends IHelloService.Stub {

	private final String TAG = "HelloService";
	private int count = 0;
	
	public void hello() throws android.os.RemoteException {		
		Log.i(TAG, "hello");  
		System.out.println("hello");
	}
	
	public int say_hello_to (String name) throws android.os.RemoteException {
		Log.i(TAG, "say hello to :" + name);  
		System.out.println("say hello to :" + name);		
		count ++;
		return count;
	}
	
}

