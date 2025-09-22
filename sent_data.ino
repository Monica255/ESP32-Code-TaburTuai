void sent_data() {
  // ini void khusus update monitoring

  json.set("temperatur", valTemp);
  json.set("humidity", valHum);
  json.set("kelembaban_tanah_1", valSoil);
  json.set("kelembaban_tanah_2", valSoil2);
  json.set("water_flow",flowRate);
  json.set("water_out",totalMilliLitres);

  Firebase.setJSON(fbdo, pathMonitoring, json);

}
