package io.agora.common;

/**
 * Created by yt on 2017/12/2.
 */

public class LeyaoyaoRoom {
    int id;
    int price;
    int currentInventory;
    int warningInventory;
    int gameTimes;
    boolean autostart;
    String status;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public int getCurrentInventory() {
        return currentInventory;
    }

    public void setCurrentInventory(int currentInventory) {
        this.currentInventory = currentInventory;
    }

    public int getWarningInventory() {
        return warningInventory;
    }

    public void setWarningInventory(int warningInventory) {
        this.warningInventory = warningInventory;
    }

    public int getGameTimes() {
        return gameTimes;
    }

    public void setGameTimes(int gameTimes) {
        this.gameTimes = gameTimes;
    }

    public boolean isAutostart() {
        return autostart;
    }

    public void setAutostart(boolean autostart) {
        this.autostart = autostart;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
