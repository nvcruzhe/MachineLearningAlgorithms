package imaginax.mlyv;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity {

    private String[] mNavigationDrawerItemTitles;
    private DrawerLayout mDrawerLayout;
    private ListView mDrawerList;
    Toolbar toolbar;
    private CharSequence mDrawerTitle;
    private CharSequence mTitle;
    android.support.v7.app.ActionBarDrawerToggle mDrawerToggle;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTitle = mDrawerTitle = getTitle();
        mNavigationDrawerItemTitles= getResources().getStringArray(R.array.navigation_drawer_items_array);
        mDrawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);
        mDrawerList = (ListView) findViewById(R.id.left_drawer);

        setupToolbar();

        DataModel[] drawerItem = new DataModel[6];
        drawerItem[0] = new DataModel(R.drawable.home , "Inicio");
        drawerItem[1] = new DataModel(R.drawable.historia, "Historia");
        drawerItem[2] = new DataModel(R.drawable.corte_esq, "Corte esquematico");
        drawerItem[3] = new DataModel(R.drawable.galeria, "Galeria de Fotos");
        drawerItem[4] = new DataModel(R.drawable.video, "Video");
        drawerItem[5] = new DataModel(R.drawable.contacto, "Contacto");

        DrawerItemCustomAdapter adapter = new DrawerItemCustomAdapter(this, R.layout.list_view_item_row, drawerItem);
        mDrawerList.setAdapter(adapter);
        mDrawerList.setOnItemClickListener(new DrawerItemClickListener());
        mDrawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);
        mDrawerLayout.setDrawerListener(mDrawerToggle);
        setupDrawerToggle();

        // Select home fragment
        Fragment fragment = new HomeFragment();
        if (fragment != null) {
            FragmentManager fragmentManager = getSupportFragmentManager();
            fragmentManager.beginTransaction().replace(R.id.content_frame, fragment).commit();
            //mDrawerList.setItemChecked(position, true);
            //mDrawerList.setSelection(position);
            setTitle(mNavigationDrawerItemTitles[0]);
            mDrawerLayout.closeDrawer(mDrawerList);
        } else {
            Log.e("MainActivity", "Error in creating fragment");
        }

    }

    private class DrawerItemClickListener implements ListView.OnItemClickListener {
        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            selectItem(position);
        }
    }

    private void selectItem(int position) {
        Fragment fragment = null;
        switch (position) {
            case 0: // Home
                fragment = new HomeFragment();
                break;
            case 1: // History
                fragment = new HistoryFragment();
                break;
            case 2: // Schematic cut
                fragment = new TransversalCut();
                break;
            case 3: // Photo Gallery
                fragment = new GalleryFragment();
                break;
            case 4: // Video
                fragment = new Video();
                break;
            case 5: // Contact
                fragment = new ContactFragment();
                break;
            default:
                break;
        }

        if (fragment != null) {
            FragmentManager fragmentManager = getSupportFragmentManager();
            fragmentManager.beginTransaction().replace(R.id.content_frame, fragment).commit();
            //mDrawerList.setItemChecked(position, true);
            //mDrawerList.setSelection(position);
            setTitle(mNavigationDrawerItemTitles[position]);
            mDrawerLayout.closeDrawer(mDrawerList);
        } else {
            Log.e("MainActivity", "Error in creating fragment");
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (mDrawerToggle.onOptionsItemSelected(item)) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void setTitle(CharSequence title) {
        mTitle = title;
        getSupportActionBar().setTitle(mTitle);
    }

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        mDrawerToggle.syncState();
    }

    void setupToolbar(){
        toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
    }

    void setupDrawerToggle(){
        mDrawerToggle = new android.support.v7.app.ActionBarDrawerToggle(this,
                mDrawerLayout,toolbar,R.string.app_name, R.string.app_name);
        //This is necessary to change the icon of the Drawer Toggle upon state change.
        mDrawerToggle.syncState();
    }
}
