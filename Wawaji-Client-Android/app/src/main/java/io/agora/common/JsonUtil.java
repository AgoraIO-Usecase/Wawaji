package io.agora.common;


import android.content.Context;
import android.content.res.AssetManager;
import android.content.res.Resources;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonElement;
import com.google.gson.JsonParseException;
import com.google.gson.JsonPrimitive;
import com.google.gson.JsonSerializationContext;
import com.google.gson.JsonSerializer;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.Type;
import java.text.DateFormat;
import java.util.Date;

public class JsonUtil {
    public static String stringify(Object bean) {
        return getGson().toJson(bean);
    }

    public static <T> T parse(String json, Type type) {
        return getGson().fromJson(json, type);
    }

    private volatile static Gson mGson;

    public static Gson getGson() {
        if (mGson == null) {
            mGson = new GsonBuilder().registerTypeAdapter(
                    java.util.Date.class, new UtilDateSerializer()).registerTypeAdapter(
                    java.util.Date.class, new UtilDateDeserializer())
                    .setDateFormat(DateFormat.LONG).create();
        }
        return mGson;
    }

    public static boolean isValidJsonString(String json) {
        try {
            new JSONObject(json);
        } catch (JSONException ex) {
            try {
                new JSONArray(json);
            } catch (JSONException ex1) {
                return false;
            }
        }
        return true;
    }

    public static String readJsonFromFile(Context ctx, String file) {
        Resources resources = ctx.getResources();
        AssetManager assetManager = resources.getAssets();
        String jsonString = null;
        InputStream inputStream = null;
        InputStreamReader inputStreamReader = null;
        BufferedReader bufferedReader = null;
        try {
            StringBuilder buffer = new StringBuilder();
            inputStream = assetManager.open(file);
            inputStreamReader = new InputStreamReader(inputStream, "UTF-8");
            bufferedReader = new BufferedReader(inputStreamReader);

            String str;
            while ((str = bufferedReader.readLine()) != null) {
                buffer.append(str);
            }

            jsonString = buffer.toString();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (bufferedReader != null) {
                try {
                    bufferedReader.close();
                } catch (IOException e) {
                }
            }
            if (inputStreamReader != null) {
                try {
                    inputStreamReader.close();
                } catch (IOException e) {
                }
            }
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (IOException e) {
                }
            }
        }
        return jsonString;
    }
}

class UtilDateSerializer implements JsonSerializer<Date> {

    public JsonElement serialize(java.util.Date src, Type typeOfSrc,
                                 JsonSerializationContext context) {
        return new JsonPrimitive(src.getTime());
    }
}

class UtilDateDeserializer implements JsonDeserializer<Date> {

    public java.util.Date deserialize(JsonElement json, Type typeOfT,
                                      JsonDeserializationContext context) throws JsonParseException {
        return new java.util.Date(json.getAsJsonPrimitive().getAsLong());
    }
}

