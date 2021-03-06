import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;

class BicycleTest {

	@ParameterizedTest
	@CsvFileSource(resources = "./speedUp_test.csv")
	public void test_speedUp(int increment, Object oracle){
		Bicycle BicycleTest = new Bicycle(/*constructor arguments*/);
		assertEquals(String.valueOf(oracle), String.valueOf(BicycleTest.speedUp(increment)),"speedUp FAILED");
	}
}