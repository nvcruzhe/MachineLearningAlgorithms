package imaginax.mlyv;

import android.app.FragmentTransaction;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

/**
 * Created by nvcruzhe on 8/20/2016.
 */
public class HomeFragment extends Fragment{
    int id;
    public HomeFragment() {
        id=0;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.home, container, false);
        id = R.id.content_frame;
        Button button = (Button) view.findViewById(R.id.keepReading);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.v("NVCH", "Emo");
                FragmentManager fm = getFragmentManager();
                android.support.v4.app.FragmentTransaction ft = fm.beginTransaction();
                HistoryFragment df = new HistoryFragment();
                ft.replace(id,df).commit();
            }
        });
        return view;
    }
}
