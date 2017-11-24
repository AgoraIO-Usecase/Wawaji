package io.agora.wawaji.app.model;

import android.app.Activity;
import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import io.agora.common.Wawaji;
import io.agora.wawaji.app.R;

/**
 * Created by beryl on 2017/10/20.
 */

public class RomListAdapter extends RecyclerView.Adapter<RomListAdapter.MyViewHolder> {

    protected final LayoutInflater mInflater;
    private Wawaji[] wawajiArr;
    private onClickButtonInterface onClickButtonInterface;

    public RomListAdapter(Context context , Wawaji[] wawajiArr ,onClickButtonInterface clickButtonInterface){
        mInflater = ((Activity) context).getLayoutInflater();
        this.wawajiArr = wawajiArr;
        this.onClickButtonInterface = clickButtonInterface;

    }



    @Override
    public void onBindViewHolder(final MyViewHolder holder, final int position) {

        holder.tvName.setText(wawajiArr[position].getName());

        holder.imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (onClickButtonInterface != null)
                    onClickButtonInterface.onItemClickListerner(position);
            }
        });

    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public int getItemCount() {
        return wawajiArr.length ;
    }

    //Override onCreateViewHolder function，return ViewHolder
    @Override
    public MyViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {

        View view = mInflater.inflate(R.layout.room_item_layout,parent, false);
        MyViewHolder holder= new MyViewHolder(view);

        return holder;
    }

    class MyViewHolder extends RecyclerView.ViewHolder {

        private TextView tvName;
        private ImageView imageView;

        public MyViewHolder(View view) {
            super(view);
            tvName = (TextView) view.findViewById(R.id.item_room_name);
            imageView = (ImageView) view.findViewById(R.id.item_room_img);
        }

    }

    public interface onClickButtonInterface{
        void onItemClickListerner(int position);

    }

}
