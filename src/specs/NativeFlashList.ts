import { TurboModule, TurboModuleRegistry } from "react-native";

export interface Spec extends TurboModule {
  install(): boolean;
}

export default TurboModuleRegistry.get<Spec>("Flashlist") as Spec | null;
