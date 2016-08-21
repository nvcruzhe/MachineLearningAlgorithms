package imaginax.mlyv;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

/**
 * Created by nvcruzhe on 8/21/2016.
 */
public class PlantaBajaFragment extends Fragment {
    public PlantaBajaFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.planta_baja, container, false);
        return rootView;
    }
}
