package imaginax.mlyv;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.widget.DrawerLayout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;

/**
 * Created by nvcruzhe on 8/21/2016.
 */
public class TransversalCut extends Fragment{
    private ListView list;
    //private DrawerLayout mDrawerLayout;
    android.support.v7.app.ActionBarDrawerToggle mDrawerToggle;

    public TransversalCut() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.transversal_cut, container, false);
        list = (ListView) rootView.findViewById(R.id.listView);

        CutModel[] drawerItem = new CutModel[3];
        drawerItem[0] = new CutModel(R.drawable.connect);
        drawerItem[1] = new CutModel(R.drawable.fixtures);
        drawerItem[2] = new CutModel(R.drawable.table);

        DrawerCutItemAdapter adapter = new DrawerCutItemAdapter(this.getContext(), R.layout.cut_view, drawerItem);

        list.setAdapter(adapter);
        list.setOnItemClickListener(new DrawerItemClickListener());

        //mDrawerLayout = (DrawerLayout) rootView.findViewById(R.id.drawer_layout);
        //mDrawerLayout.setDrawerListener(mDrawerToggle);

        return rootView;
    }

    private class DrawerItemClickListener implements ListView.OnItemClickListener {
        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            selectItem(position);
        }
    }

    private void selectItem(int position) {
        android.support.v4.app.Fragment fragment = null;
        switch (position) {
            case 0: // Planta Alta
                fragment = new PlantaAltaFragment();
                break;
            case 1: // Planta Media
                fragment = new PlantaMediaFragment();
                break;
            case 2: // Planta Baja
                fragment = new PlantaBajaFragment();
                break;
            default:
                break;
        }

        if (fragment != null) {
            FragmentManager fragmentManager = getFragmentManager();
            fragmentManager.beginTransaction().replace(R.id.content_specific, fragment).commit();
            //mDrawerLayout.closeDrawer(list);
        } else {
            Log.e("MainActivity", "Error in creating fragment");
        }
    }
}
