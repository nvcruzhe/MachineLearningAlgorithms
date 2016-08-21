package imaginax.mlyv;

import android.support.v4.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Gallery;
import android.widget.ImageView;

/**
 * Created by nvcruzhe on 8/21/2016.
 */
public class GalleryFragment extends Fragment{
    Gallery Imagegallery;
    Integer[] GalleryImagesList =
            {
                    R.drawable.one,
                    R.drawable.two,
                    R.drawable.three,
                    R.drawable.four,
                    R.drawable.five,
                    R.drawable.six,
                    R.drawable.seven
            };
    ImageView imgGalleryImage;

    public GalleryFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.gallery, container, false);
        imgGalleryImage = (ImageView) view.findViewById(R.id.imgGalleryImage);
        imgGalleryImage.setImageResource(R.drawable.one);

        Imagegallery = (Gallery) view.findViewById(R.id.gallery);
        Imagegallery.setAdapter(new ImageAdapter(getActivity().getApplicationContext()));
        return view;
    }

    private class ImageAdapter extends BaseAdapter {
        Context context;
        public ImageAdapter(Context context){
            this.context = context;
        }

        @Override
        public int getCount(){
            return GalleryImagesList.length;
        }

        @Override
        public Object getItem(int position){
            return GalleryImagesList[position];
        }

        @Override
        public long getItemId(int position){
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent){
            ImageView imageView = new ImageView(this.context);
            imageView.setImageResource(GalleryImagesList[position]);
            imageView.setLayoutParams(new Gallery.LayoutParams(150, 200));
            imageView.setScaleType(ImageView.ScaleType.FIT_XY);
            return imageView;
        }

    }
}
