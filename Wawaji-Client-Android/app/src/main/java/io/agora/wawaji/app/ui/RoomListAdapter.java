package io.agora.wawaji.app.ui;

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

public class RoomListAdapter extends RecyclerView.Adapter<RoomListAdapter.MyViewHolder> {

    protected final LayoutInflater mInflater;
    private Wawaji[] wawajiArr;
    private onClickButtonInterface onClickButtonInterface;

    public RoomListAdapter(Context context, Wawaji[] wawajiArr, onClickButtonInterface clickButtonInterface) {
        mInflater = ((Activity) context).getLayoutInflater();
        this.wawajiArr = wawajiArr;
        this.onClickButtonInterface = clickButtonInterface;

    }

    @Override
    public void onBindViewHolder(final MyViewHolder holder, final int position) {

        switch (position % 4){
            case 0:
                holder.imageView.setBackgroundResource(R.drawable.img_one);
                break;
            case 1:
                holder.imageView.setBackgroundResource(R.drawable.img_two);
                break;
            case 2:
                holder.imageView.setBackgroundResource(R.drawable.img_three);
                break;
            case 3:
                holder.imageView.setBackgroundResource(R.drawable.img_four);
                break;
        }
        if (position % 2 == 0){
            holder.imageStatus.setBackgroundResource(R.drawable.available);
        }else {
            holder.imageStatus.setBackgroundResource(R.drawable.busy);
        }

        holder.imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (onClickButtonInterface != null)
                    onClickButtonInterface.onItemClickListener(position);
            }
        });

    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public int getItemCount() {
        return wawajiArr.length;
    }

    @Override
    public MyViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {

        View view = mInflater.inflate(R.layout.room_item_layout, parent, false);
        MyViewHolder holder = new MyViewHolder(view);

        return holder;
    }

    class MyViewHolder extends RecyclerView.ViewHolder {

        private TextView tvName;
        private ImageView imageView;
        private ImageView imageStatus;

        public MyViewHolder(View view) {
            super(view);
            tvName      = (TextView) view.findViewById(R.id.item_room_name);
            imageView   = (ImageView) view.findViewById(R.id.item_room_img);
            imageStatus = (ImageView) view.findViewById(R.id.item_room_state);
        }

    }

    public interface onClickButtonInterface {
        void onItemClickListener(int position);
    }

}
