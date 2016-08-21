package imaginax.mlyv;

import android.app.ProgressDialog;
import android.media.MediaPlayer;
import android.net.Uri;
import android.support.v4.app.Fragment;
import android.media.session.MediaController;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;
import android.widget.VideoView;

import java.io.File;

/**
 * Created by nvcruzhe on 8/21/2016.
 */
public class Video extends Fragment {
    private VideoView videoView;
    private MediaController mediaController;
    private int position = 0;
    private ProgressDialog progressDialog;

    public Video(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.video, container, false);
        videoView = (VideoView) rootView.findViewById(R.id.video);
        videoView.setVideoURI(Uri.parse("android.resource://" + getActivity().getApplicationContext().getPackageName() +
                "/" + R.raw.palalacio_pasado));
        videoView.requestFocus();
        videoView.start();
        return rootView;
    }


}
