void get_status() {
  // Get status from firebase

  Serial.printf("Get int pompa_1... %s\n", Firebase.getInt(fbdo, pathPompaK1, &statePompa1) ? String(statePompa1).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int pompa_2... %s\n", Firebase.getInt(fbdo, pathPompaK2, &statePompa2) ? String(statePompa2).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int pompa_3... %s\n", Firebase.getInt(fbdo, pathPompaK3, &statePompa3) ? String(statePompa3).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int pompa_4... %s\n", Firebase.getInt(fbdo, pathPompaK4, &statePompa4) ? String(statePompa4).c_str() : fbdo.errorReason().c_str());

  Serial.printf("Get int selenoid_1... %s\n", Firebase.getInt(fbdo, pathSelenoid1, &stateSelenoid1) ? String(stateSelenoid1).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_2... %s\n", Firebase.getInt(fbdo, pathSelenoid2, &stateSelenoid2) ? String(stateSelenoid2).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_3... %s\n", Firebase.getInt(fbdo, pathSelenoid3, &stateSelenoid3) ? String(stateSelenoid3).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_4... %s\n", Firebase.getInt(fbdo, pathSelenoid4, &stateSelenoid4) ? String(stateSelenoid4).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_5... %s\n", Firebase.getInt(fbdo, pathSelenoid5, &stateSelenoid5) ? String(stateSelenoid5).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_6... %s\n", Firebase.getInt(fbdo, pathSelenoid6, &stateSelenoid6) ? String(stateSelenoid6).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_7... %s\n", Firebase.getInt(fbdo, pathSelenoid7, &stateSelenoid7) ? String(stateSelenoid7).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_8... %s\n", Firebase.getInt(fbdo, pathSelenoid8, &stateSelenoid8) ? String(stateSelenoid8).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_9... %s\n", Firebase.getInt(fbdo, pathSelenoid9, &stateSelenoid9) ? String(stateSelenoid9).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int selenoid_10... %s\n", Firebase.getInt(fbdo, pathSelenoid10, &stateSelenoid10) ? String(stateSelenoid10).c_str() : fbdo.errorReason().c_str());


  digitalWrite(POMPA1PIN, statePompa1);
  digitalWrite(POMPA2PIN, statePompa2);
  digitalWrite(POMPA3PIN, statePompa3);
  digitalWrite(POMPA4PIN, statePompa4);

  digitalWrite(SELENOID1PIN, stateSelenoid1);
  digitalWrite(SELENOID2PIN, stateSelenoid2);
  digitalWrite(SELENOID3PIN, stateSelenoid3);
  digitalWrite(SELENOID4PIN, stateSelenoid4);
  digitalWrite(SELENOID5PIN, stateSelenoid5);
  digitalWrite(SELENOID6PIN, stateSelenoid6);
  digitalWrite(SELENOID7PIN, stateSelenoid7);
  digitalWrite(SELENOID8PIN, stateSelenoid8);
  digitalWrite(SELENOID9PIN, stateSelenoid9);
  digitalWrite(SELENOID10PIN, stateSelenoid10);

}
